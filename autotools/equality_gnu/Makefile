MY_VARIABLE = some_value

ifeq ($(MY_VARIABLE),some_value)
EXTRA_DIST = file1.txt file2.txt
else
EXTRA_DIST = file3.txt
endif

.PHONY: default
default:
	echo $(EXTRA_DIST)
