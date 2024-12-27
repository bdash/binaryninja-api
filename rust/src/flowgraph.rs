// Copyright 2021-2024 Vector 35 Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//! Interfaces for creating and displaying pretty CFGs in Binary Ninja.

use crate::disassembly::DisassemblyTextLine;
use binaryninjacore_sys::*;
use std::slice;

use crate::rc::*;

use crate::basic_block::{BasicBlock, BlockContext};
use crate::function::HighlightColor;
use crate::render_layer::CoreRenderLayer;
use std::marker::PhantomData;

pub type BranchType = BNBranchType;
pub type EdgePenStyle = BNEdgePenStyle;
pub type ThemeColor = BNThemeColor;
pub type FlowGraphOption = BNFlowGraphOption;

#[derive(PartialEq, Eq, Hash)]
pub struct FlowGraph {
    pub(crate) handle: *mut BNFlowGraph,
}

impl FlowGraph {
    pub(crate) unsafe fn from_raw(raw: *mut BNFlowGraph) -> Self {
        Self { handle: raw }
    }

    pub(crate) unsafe fn ref_from_raw(raw: *mut BNFlowGraph) -> Ref<Self> {
        Ref::new(Self { handle: raw })
    }

    pub fn new() -> Ref<Self> {
        unsafe { FlowGraph::ref_from_raw(BNCreateFlowGraph()) }
    }

    pub fn nodes<'a>(&self) -> Vec<Ref<FlowGraphNode<'a>>> {
        let mut count: usize = 0;
        let nodes_ptr = unsafe { BNGetFlowGraphNodes(self.handle, &mut count as *mut usize) };

        let nodes = unsafe { slice::from_raw_parts_mut(nodes_ptr, count) };

        let mut result = vec![];
        result.reserve(count);

        for i in 0..count {
            result.push(unsafe { RefCountable::inc_ref(&FlowGraphNode::from_raw(nodes[i])) });
        }

        unsafe { BNFreeFlowGraphNodeList(nodes_ptr, count) };

        result
    }

    pub fn get_node<'a>(&self, i: usize) -> Option<Ref<FlowGraphNode<'a>>> {
        let node_ptr = unsafe { BNGetFlowGraphNode(self.handle, i) };
        if node_ptr.is_null() {
            None
        } else {
            Some(unsafe { Ref::new(FlowGraphNode::from_raw(node_ptr)) })
        }
    }

    pub fn get_node_count(&self) -> usize {
        unsafe { BNGetFlowGraphNodeCount(self.handle) }
    }

    pub fn has_nodes(&self) -> bool {
        unsafe { BNFlowGraphHasNodes(self.handle) }
    }

    pub fn append(&self, node: &FlowGraphNode) -> usize {
        unsafe { BNAddFlowGraphNode(self.handle, node.handle) }
    }

    pub fn replace(&self, index: usize, node: &FlowGraphNode) {
        unsafe { BNReplaceFlowGraphNode(self.handle, index, node.handle) }
    }

    pub fn clear(&self) {
        unsafe { BNClearFlowGraphNodes(self.handle) }
    }

    pub fn set_option(&self, option: FlowGraphOption, value: bool) {
        unsafe { BNSetFlowGraphOption(self.handle, option, value) }
    }

    pub fn is_option_set(&self, option: FlowGraphOption) -> bool {
        unsafe { BNIsFlowGraphOptionSet(self.handle, option) }
    }

    /// A list of the currently applied [`CoreRenderLayer`]'s
    pub fn render_layers(&self) -> Array<CoreRenderLayer> {
        let mut count: usize = 0;
        unsafe {
            let handles = BNGetFlowGraphRenderLayers(self.handle, &mut count);
            Array::new(handles, count, ())
        }
    }

    /// Add a Render Layer to be applied to this [`FlowGraph`].
    ///
    /// NOTE: Layers will be applied in the order in which they are added.
    pub fn add_render_layer(&self, layer: &CoreRenderLayer) {
        unsafe { BNAddFlowGraphRenderLayer(self.handle, layer.handle.as_ptr()) };
    }

    /// Remove a Render Layer from being applied to this [`FlowGraph`].
    pub fn remove_render_layer(&self, layer: &CoreRenderLayer) {
        unsafe { BNRemoveFlowGraphRenderLayer(self.handle, layer.handle.as_ptr()) };
    }
}

unsafe impl RefCountable for FlowGraph {
    unsafe fn inc_ref(handle: &Self) -> Ref<Self> {
        Ref::new(Self {
            handle: BNNewFlowGraphReference(handle.handle),
        })
    }

    unsafe fn dec_ref(handle: &Self) {
        BNFreeFlowGraph(handle.handle);
    }
}

impl ToOwned for FlowGraph {
    type Owned = Ref<Self>;

    fn to_owned(&self) -> Self::Owned {
        unsafe { RefCountable::inc_ref(self) }
    }
}

#[derive(PartialEq, Eq, Hash)]
pub struct FlowGraphNode<'a> {
    pub(crate) handle: *mut BNFlowGraphNode,
    _data: PhantomData<&'a ()>,
}

impl<'a> FlowGraphNode<'a> {
    pub(crate) unsafe fn from_raw(raw: *mut BNFlowGraphNode) -> Self {
        Self {
            handle: raw,
            _data: PhantomData,
        }
    }

    pub(crate) unsafe fn ref_from_raw(raw: *mut BNFlowGraphNode) -> Ref<Self> {
        Ref::new(Self {
            handle: raw,
            _data: PhantomData,
        })
    }

    pub fn new(graph: &FlowGraph) -> Ref<Self> {
        unsafe { FlowGraphNode::ref_from_raw(BNCreateFlowGraphNode(graph.handle)) }
    }

    pub fn basic_block<C: BlockContext>(&self, context: C) -> Option<Ref<BasicBlock<C>>> {
        let block_ptr = unsafe { BNGetFlowGraphBasicBlock(self.handle) };
        if block_ptr.is_null() {
            return None;
        }
        Some(unsafe { BasicBlock::ref_from_raw(block_ptr, context) })
    }

    pub fn set_basic_block<C: BlockContext>(&self, block: Option<&BasicBlock<C>>) {
        match block {
            Some(block) => unsafe { BNSetFlowGraphBasicBlock(self.handle, block.handle) },
            None => unsafe { BNSetFlowGraphBasicBlock(self.handle, std::ptr::null_mut()) },
        }
    }

    pub fn lines(&self) -> Array<DisassemblyTextLine> {
        let mut count = 0;
        let result = unsafe { BNGetFlowGraphNodeLines(self.handle, &mut count) };
        assert!(!result.is_null());
        unsafe { Array::new(result, count, ()) }
    }

    pub fn set_lines(&self, lines: impl IntoIterator<Item = DisassemblyTextLine>) {
        // NOTE: This will create allocations and increment tag refs, we must call DisassemblyTextLine::free_raw
        let mut raw_lines: Vec<BNDisassemblyTextLine> = lines
            .into_iter()
            .map(DisassemblyTextLine::into_raw)
            .collect();
        unsafe {
            BNSetFlowGraphNodeLines(self.handle, raw_lines.as_mut_ptr(), raw_lines.len());
            for raw_line in raw_lines {
                DisassemblyTextLine::free_raw(raw_line);
            }
        }
    }

    /// Returns the graph position of the node in X, Y form.
    pub fn position(&self) -> (i32, i32) {
        let pos_x = unsafe { BNGetFlowGraphNodeX(self.handle) };
        let pos_y = unsafe { BNGetFlowGraphNodeY(self.handle) };
        (pos_x, pos_y)
    }

    /// Sets the graph position of the node.
    pub fn set_position(&self, x: i32, y: i32) {
        unsafe { BNFlowGraphNodeSetX(self.handle, x) };
        unsafe { BNFlowGraphNodeSetX(self.handle, y) };
    }

    pub fn highlight_color(&self) -> HighlightColor {
        let raw = unsafe { BNGetFlowGraphNodeHighlight(self.handle) };
        HighlightColor::from(raw)
    }

    pub fn set_highlight_color(&self, highlight: HighlightColor) {
        unsafe { BNSetFlowGraphNodeHighlight(self.handle, highlight.into()) };
    }

    // TODO: Add getters and setters for edges

    pub fn add_outgoing_edge(
        &self,
        type_: BranchType,
        target: &'a FlowGraphNode,
        edge_style: EdgeStyle,
    ) {
        unsafe {
            BNAddFlowGraphNodeOutgoingEdge(self.handle, type_, target.handle, edge_style.into())
        }
    }
}

unsafe impl RefCountable for FlowGraphNode<'_> {
    unsafe fn inc_ref(handle: &Self) -> Ref<Self> {
        Ref::new(Self {
            handle: BNNewFlowGraphNodeReference(handle.handle),
            _data: PhantomData,
        })
    }

    unsafe fn dec_ref(handle: &Self) {
        BNFreeFlowGraphNode(handle.handle);
    }
}

impl ToOwned for FlowGraphNode<'_> {
    type Owned = Ref<Self>;

    fn to_owned(&self) -> Self::Owned {
        unsafe { RefCountable::inc_ref(self) }
    }
}

#[derive(Clone, Copy, PartialEq, Eq, Hash, Debug)]
pub struct EdgeStyle {
    style: EdgePenStyle,
    width: usize,
    color: ThemeColor,
}

impl EdgeStyle {
    pub fn new(style: EdgePenStyle, width: usize, color: ThemeColor) -> Self {
        Self {
            style,
            width,
            color,
        }
    }
}

impl Default for EdgeStyle {
    fn default() -> Self {
        Self::new(EdgePenStyle::SolidLine, 0, ThemeColor::AddressColor)
    }
}

impl From<BNEdgeStyle> for EdgeStyle {
    fn from(style: BNEdgeStyle) -> Self {
        Self::new(style.style, style.width, style.color)
    }
}

impl From<EdgeStyle> for BNEdgeStyle {
    fn from(style: EdgeStyle) -> Self {
        Self {
            style: style.style,
            width: style.width,
            color: style.color,
        }
    }
}
