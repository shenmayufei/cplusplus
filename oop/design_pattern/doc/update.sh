#!/bin/bash

for name in `ls .`; do
	new_name=$(echo "${name}" | awk '{gsub("设计模式", "_design_patterns_"); print}')
	new_name=$(echo "${new_name}" | awk '{gsub("课件和代码", "_doc_"); print}')
	new_name=$(echo "${new_name}" | awk '{gsub("课件", "_doc_"); print}')
	mv "${name}" "${new_name}"
done
