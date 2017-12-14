#! /bin/bash

set -o nounset
set -o physical
set -o errexit

# directories and paths #####################################################

ORIG_DIR="$(pwd -P)"
SCRIPT_DIR=$(dirname "${BASH_SOURCE[0]}")

cd "$SCRIPT_DIR/.."
VULKAN_TOOLS="$(pwd -P)"
VT_BUILD_DIR="$VULKAN_TOOLS/build"
VT_LVL_BUILD_DIR="$VT_BUILD_DIR/submodules/Vulkan-LoaderAndValidationLayers"
cd "$VT_BUILD_DIR/tests"

# OS settings ###############################################################

export LD_LIBRARY_PATH="$VT_LVL_BUILD_DIR/loader:${LD_LIBRARY_PATH:-}"

unset DISPLAY
#export DISPLAY=":0"

# Loader settings ###########################################################

unset VK_LAYER_PATH
export VK_LAYER_PATH="$VT_BUILD_DIR/layersvt"

unset VK_INSTANCE_LAYERS
export VK_INSTANCE_LAYERS="VK_LAYER_LUNARG_device_simulation"

unset VK_LOADER_DEBUG
#export VK_LOADER_DEBUG="info"
#export VK_LOADER_DEBUG="all"

# DevSim settings ###########################################################

# Get latest VK_DEVSIM_FILENAME from $VULKAN_TOOLS/tests/devsim_layer_test.sh
unset VK_DEVSIM_FILENAME
export VK_DEVSIM_FILENAME="devsim_test2_in1.json:devsim_test2_in2.json:devsim_test2_in3.json:devsim_test2_in4.json:devsim_test2_in5.json:devsim_test2_in6.json"

unset VK_DEVSIM_DEBUG_ENABLE
#export VK_DEVSIM_DEBUG_ENABLE=1

unset VK_DEVSIM_EXIT_ON_ERROR
#export VK_DEVSIM_EXIT_ON_ERROR=1

# If enable_environment exists, then the envar _must_ be set to enable the layer.
unset VK_DEVSIM_130_LAYER_ENABLE
export VK_DEVSIM_130_LAYER_ENABLE=1

unset VK_DEVSIM_130_LAYER_DISABLE
#export VK_DEVSIM_130_LAYER_DISABLE=1

# app invocation ############################################################

$VT_LVL_BUILD_DIR/demos/vulkaninfo -j
echo "result = $?"

# vim: set sw=4 ts=8 et ic ai:
