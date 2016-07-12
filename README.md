# Compiler Final Project

## 執行環境
Ubuntu 14.04 with gcc 4.8.2

## 執行方式
1. make
2. ./ccompiler <filename>

## 實作方式
主要功能皆實作於 ccompiler.y，方法為使用 yacc bottom up 的將每一個樹節點串接起來，完成後再 top-down 去遞迴的遍歷這顆語法樹產生 mips code。

## 備註
1.由於該語法樹在 operation 上屬於右結合，故本編譯器配合其邏輯實作之，比如以下情形：
```
1+3-5 = (1+(3-5)) = -1
```
2.test 資料夾中存放了通過測試的實驗碼，可以產生出正確的mips code。
