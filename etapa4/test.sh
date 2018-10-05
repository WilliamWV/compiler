make > dump
##### Adicionar arquivos de teste como foi feito com o arquivo correctEntries #####
./etapa4 < tests/correctEntries > firstOutput
./etapa4 < firstOutput > secondOutput
diff firstOutput secondOutput
echo $?

##### Remoção de arquivos temporários #####
rm -rf dump
rm -rf firstOutput
rm -rf secondOutput

