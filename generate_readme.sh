# 打包子目录下所有README到当前目录
file_name="README.md"

rm -f $file_name
#find ./ -name $file_name -type f -exec cat {} + >> template.md

for file in $(find $FILE_DIR -type f -name "$file_name" | sort); do
    echo FILE: $file

    # file_load=$(echo "$file" | sed "s/\/$file_name//g")
    # echo "> 项目仓库：[$file_load]($file_load)"  >> template.md

    file_load=$(echo "$file" | sed "s#^\./##; s#/$file_name##g")
    echo "# [$file_load]($file_load)"  >> template.md
    cat $file >> template.md
    echo >> template.md
    echo "---------------------------"  >> template.md
done

mv template.md $file_name
echo OUTFILE: $file_name


