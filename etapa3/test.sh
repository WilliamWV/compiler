make > dump
##### Adicionar arquivos de teste como foi feito com o arquivo correctEntries #####
cat correctEntries | ./etapa3 > firstOutput
cat firstOutput | ./etapa3 > secondOutput
diff firstOutput secondOutput
echo $?

##### Remoção de arquivos temporários #####
rm -rf dump
rm -rf firstOutput
rm -rf secondOutput

