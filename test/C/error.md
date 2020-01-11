p != NULL在字符串做为结束循环的标识不一定成立
反面教材是curl.c的36行的while语句
     /*while(p != NULL)//将'/'之后的字符复制到FileNameTmp
   37     {
   38         *fnamep = *p;
   39         p++;
   40         fnamep++;
   41     }*/
