#! /bin/sh -x

source 100_setup-env.sh

export VK_DEVSIM_DEBUG_ENABLE="1"
#export VK_DEVSIM_EXIT_ON_ERROR="1"
#export VK_LOADER_DEBUG="all"

${HOME}/lvl/BUILD/demos/vulkaninfo -j

#############################################################################

# Use jq to extract, sort, and reformat the JSON files.
#jq -S '{properties,features,memory,queues,formats}' ${FILENAME_01_GOLD} > ${FILENAME_01_TEMP1}
#jq -S '{properties,features,memory,queues,formats}' ${FILENAME_01_RESULT} > ${FILENAME_01_TEMP2}

# Compare files with diff
#diff ${FILENAME_01_TEMP1} ${FILENAME_01_TEMP2}
#[ $? -eq 0 ] || ERRMSG="diff file compare failed"

# Compare files with jq
#jq --slurp --exit-status '.[0] == .[1]' ${FILENAME_01_GOLD} ${FILENAME_01_TEMP1}
#[ $? -eq 0 ] || ERRMSG="jq file compare failed"

# vim: set sw=4 ts=8 et ic ai:
