
IMPLICIT_LAYER_DIR = ${HOME}/.local/share/vulkan/implicit_layer.d

VULKAN_TOOLS = ${HOME}/vt
VT_TESTS_DIR = ${VULKAN_TOOLS}/build/tests

.PHONY: all
all: ${VT_TESTS_DIR} build_devsim link test unlink show

.PHONY: test
test:
	# VULKAN_TOOLS = ${VULKAN_TOOLS}
	# IMPLICIT_LAYER_DIR = ${IMPLICIT_LAYER_DIR}
	rm -f vinfo_out.txt
	./vulkaninfo_test.sh > vinfo_out.txt

.PHONY: build_devsim
build_devsim:
	make -C .. -j

.PHONY: clean_devsim
clean_devsim:
	make -C .. clean

${VT_TESTS_DIR}:
	exit 20

.PHONY: show
show:
	git diff vinfo_out.txt

.PHONY: link
link:
	rm -rf ${IMPLICIT_LAYER_DIR}
	mkdir -p ${IMPLICIT_LAYER_DIR}
	ln -s ${VULKAN_TOOLS}/layersvt/linux/VkLayer_device_simulation_IMPLICIT.json ${IMPLICIT_LAYER_DIR}
	ln -s ${VULKAN_TOOLS}/build/layersvt/libVkLayer_device_simulation.so ${IMPLICIT_LAYER_DIR}

.PHONY: unlink
unlink:
	rm -rf ${IMPLICIT_LAYER_DIR}

# vim: set sw=4 ts=8 noet ic ai:
