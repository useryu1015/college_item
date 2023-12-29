# 打包子目录下所有README到当前目录
file_name="README.md"

rm -f $file_name
#find ./ -name $file_name -type f -exec cat {} + >> template.md

find ./ -name "$file_name" -type f -exec sh -c 'echo "File: $0" >> template.md; cat "$0" >> template.md; echo "---------------------------" >> template.md' {} \;


mv template.md $file_name
