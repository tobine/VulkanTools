#! /bin/bash

set -o nounset
set -o physical
set -o errexit

cd tests

JSON_SECTIONS='{VkPhysicalDeviceProperties,VkPhysicalDeviceFeatures,VkPhysicalDeviceMemoryProperties,ArrayOfVkQueueFamilyProperties,ArrayOfVkFormatProperties}'
IN_FILES='devsim_test2_in*.json'
OUT_FILE='devsim_test2_gold.json'

cat $IN_FILES | jq -s add | jq -S $JSON_SECTIONS > $OUT_FILE

# someday I'll figure out how to do the residual editing with jq
echo "Done, but you still need to manually edit $OUT_FILE"

# vim: set sw=4 ts=8 et ic ai:
