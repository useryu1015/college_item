#!/usr/bin/python3
# -*- coding: utf-8 -*-
# main.py
# ...
import os

file_name = "README.md"
file_dir = "./"
# os.remove(file_name)

with open(file_name, "w") as output_file:
    # os.remove(file_name)
    for root, dirs, files in os.walk(file_dir):
        for file in sorted(files):
            if file == file_name:
                file_path = os.path.join(root, file)
                with open(file_path, "r") as input_file:
                    output_file.write(input_file.read())
                    output_file.write("> 项目仓库：[{}]({})\n".format(root, root))
                    output_file.write("---------------------------\n")
                print("FILE: {}".format(file_path))

print("合并完成，输出文件：{}".format(file_name))
