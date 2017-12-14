# source this file into an existing shell.

LVL="${HOME}/gits/github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers"
VT="${HOME}/gits/github.com/LunarG/VulkanTools"
FLAVOR="build"
#FLAVOR="dbuild"

# system envars
export PATH="$LVL/$FLAVOR/demos:$LVL/$FLAVOR/libs/vkjson:${PATH:-}"
export LD_LIBRARY_PATH="$LVL/$FLAVOR/loader:${LD_LIBRARY_PATH:-}"

# loader envars
export VK_LAYER_PATH="$VT/$FLAVOR/layersvt:$LVL/$FLAVOR/layers"
export VK_INSTANCE_LAYERS="VK_LAYER_LUNARG_device_simulation"
#export VK_LOADER_DEBUG="all"

# devsim envars
export VK_DEVSIM_FILENAME="$VT/tests/devsim_test1_in_ArrayOfVkFormatProperties.json:$VT/tests/devsim_test1_in.json:$VT/tests/devsim_test1_in_ArrayOfVkExtensionProperties.json"
export VK_DEVSIM_DEBUG_ENABLE="1"
#export VK_DEVSIM_EXIT_ON_ERROR="1"

unset LVL VT FLAVOR

# vim: set sw=4 ts=8 et ic ai:
