#!/bin/bash
$url="http://book.zongheng.com/chapter/672340/36898237.html";  


$ch=curl_init($url);

curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

$output=curl_exec($ch);

curl_close($ch);
//匹配标题            <div class="title_txtbox">第一章 惊蛰</div>
preg_match_all("/<div class=\"title_txtbox\">(.*?)<\/div>/", $output, $title);    
//匹配p标签段落内容    <p>二月二，龙抬头。</p>
preg_match_all("/<p>(.*?)<\/p>/", $output, $match);

//.  是任意字符 可以匹配任何单个字符，
//.*？  表示匹配任意字符到下一个符合条件的字符
$a=$match[0];
echo implode( ' ',$a);
