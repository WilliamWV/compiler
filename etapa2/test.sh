#!/bin/bash
make > dump
#Testes que devem ser corretos sintaticamente devem ser postos no arquivo correctEntries
cat correctEntries | ./etapa2 > output
diff output emptyFile

#Testes que devem ser sintaticamente errados devem ser postos abaixo seguindo o esquema:
#	> echo <testEntry> | ./etapa2 > output
#	> diff output errorFile

# Testes que possuem erro sintático para tipos definidos pelo usuário
echo class | ./etapa2 > output
diff output errorFile

echo class [private int a]| ./etapa2 > output
diff output errorFile

echo class c [private protected string j]| ./etapa2 > output
diff output errorFile

echo class d[abc]| ./etapa2 > output
diff output errorFile

echo class d[private a: private b]| ./etapa2 > output
diff output errorFile

echo class d[private int a, private int b]| ./etapa2 > output
diff output errorFile

#Testes que possuem erro sintático para variáveis globais

echo nosemicolon int | ./etapa2 > output
diff output errorFile

echo int typeFirst\;| ./etapa2 > output
diff output errorFile

echo sizeUndef [] static int\;| ./etapa2 > output
diff output errorFile

#echo stringOnSize [\"12\"] float\;| ./etapa2 > output
diff output errorFile

echo noType \; | ./etapa2 > output
diff output errorFile

echo int\;| ./etapa2 > output
diff output errorFile

#Testes que possuem erro sintático para definição de funções

echo static onlyStatic\(int a\)\{\} | ./etapa2 > output
diff output errorFile

echo int noComma \(const string j float a\)\{\}| ./etapa2 > output
diff output errorFile

echo int noBody \(\)| ./etapa2 > output
diff output errorFile

echo float unexpStatic\(int a, static int b\)\{\}| ./etapa2 > output
diff output errorFile

echo const float unexpConst\(int i\)\{\}| ./etapa2 > output
diff output errorFile

echo int semicolonOnEnt\(int a, float b\)\{\}\;| ./etapa2 > output
diff output errorFile

#Blocos de comandos - Precisam de mais testes quando comandos simples estiverem disponíveis

echo int foo\(\)\{"/*"Unbalanced brackets"*/"\}\}| ./etapa2 > output
diff output errorFile


make clean > dump
rm -rf dump 
rm -rf output

#No final, se todos os testes sairem como esperado a saída no terminal deve ser vazia
