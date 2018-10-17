make > dump
##### Adicionar arquivos de teste como foi feito com o arquivo correctEntries #####

for i in $(ls tests/automatic); do
	./etapa4<tests/automatic/$i > dump
	echo $i $?
done

make clean > dump
rm -rf dump
