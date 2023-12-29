#将一个文件转码，使用了一个中转文件
 
echo $1
iconv -f GB2312 -t UTF-8 -o iconv_template $1
cp iconv_template $1
rm iconv_template


