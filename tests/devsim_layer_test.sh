#! /bin/bash
# Simple test of devsim layer
# Uses 'jq' v1.5 (https://stedolan.github.io/jq/) to extract sections of
# test's JSON output and reformat for consistent comparison with gold file.

set errexit
set nounset
set physical

cd $(dirname "${BASH_SOURCE[0]}")

if [ -t 1 ] ; then
    RED='\033[0;31m'
    GREEN='\033[0;32m'
    NC='\033[0m' # No Color
else
    RED=''
    GREEN=''
    NC=''
fi

printf "$GREEN[ RUN      ]$NC $0\n"

export LD_LIBRARY_PATH=${PWD}/../submodules/Vulkan-LoaderAndValidationLayers/loader:${LD_LIBRARY_PATH}
export VK_LAYER_PATH=${PWD}/../layersvt
export VK_INSTANCE_LAYERS="VK_LAYER_LUNARG_device_simulation"

#export VK_DEVSIM_DEBUG_ENABLE="1"
#export VK_DEVSIM_EXIT_ON_ERROR="1"
#export VK_LOADER_DEBUG="all"

#############################################################################
# Test #1 VkJson_Info test

VKJSON_INFO="${PWD}/../submodules/Vulkan-LoaderAndValidationLayers/libs/vkjson/vkjson_info"

FILENAME_01_IN="devsim_test1_in_ArrayOfVkFormatProperties.json:devsim_test1_in.json"
FILENAME_01_GOLD="devsim_test1_gold.json"
FILENAME_01_RESULT="device_simulation_layer_test_1.json"
FILENAME_01_STDOUT="device_simulation_layer_test_1.txt"

export VK_DEVSIM_FILENAME="${FILENAME_01_IN}"
${VKJSON_INFO} > ${FILENAME_01_STDOUT}

# reformat/extract/sort vkjson output using jq, then compare against gold.
diff ${FILENAME_01_GOLD} \
    <(jq -S '{properties,features,memory,queues,formats}' ${FILENAME_01_RESULT}) \
    >> ${FILENAME_01_STDOUT}
RES=$?
rm ${FILENAME_01_RESULT}
rm ${FILENAME_01_STDOUT}

#############################################################################

if [ "$RES" -eq 0 ] ; then
   printf "$GREEN[  PASSED  ]$NC ${PGM}\n"
else
   printf "$RED[  FAILED  ]$NC vkjson file compare failed\n"
   printf "TEST FAILED\n"
   exit 1
fi

#############################################################################
# Test #2 VulkanInfo test

VULKANINFO="${PWD}/../submodules/Vulkan-LoaderAndValidationLayers/demos/vulkaninfo"

FILENAME_02_IN="${PWD}/../submodules/Vulkan-LoaderAndValidationLayers/demos/vulkaninfo.json"
FILENAME_02_OUT="vulkaninfo_test_2.json"
FILENAME_02_DIFF="vulkaninfo_diff.txt"

export VK_DEVSIM_FILENAME="${FILENAME_02_IN}"

${VULKANINFO} -j > ${FILENAME_02_OUT}

diff ${FILENAME_02_IN} ${FILENAME_02_OUT} > ${FILENAME_02_DIFF}
RES=$?
rm ${FILENAME_02_DIFF}
rm ${FILENAME_02_OUT}

#############################################################################

if [ "$RES" -eq 0 ] ; then
   printf "$GREEN[  PASSED  ]$NC ${PGM}\n"
else
   printf "$RED[  FAILED  ]$NC vulkaninfo file compare failed\n"
   printf "TEST FAILED\n"
   exit 1
fi

exit 0

# vim: set sw=4 ts=8 et ic ai:
