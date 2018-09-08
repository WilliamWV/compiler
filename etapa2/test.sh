#!/bin/bash
make > dump
#Testes que devem ser corretos sintaticamente devem ser postos no arquivo correctEntries
cat correctEntries | ./etapa2 > output
diff output emptyFile

# Para testes que devem ser sintaticamente errados foi criado
# o programa expectedErrorReport que gera a saída esperada pelo
# parser recebendo:
#	1) O token inexperado que será encontrado
#	2) O token que deveria estar presente
#	3) A linha em que o erro deve ser identificado
# Os erros podem então serem testados com:
# cat <file> | ./etapa2 > output
# ./EFG expectedErrorReport <unexpectedTK> <expectedTK> <line>
# diff output expectedErrorReport
rm -rf errorReportOutput # clean the file
for f in $(ls ./testsWithError); do
	cat ./testsWithError/$f | ./etapa2 >> errorReportOutput 
done

diff errorReportOutput expectedErrorReport


make clean > dump
rm -rf dump 
rm -rf output

#No final, se todos os testes sairem como esperado a saída no terminal deve ser vazia
