#!/bin/bash

# le Shebang

# Verification de nombre darguments
[ $# -lt 1 ] && exit 1
# ecrire le shebang que on rediraction à larchive my-ball
 
cat << end >> my-ball.sh
#!/bin/bash
end

# faire une boucle pour parcourir tous les arguments saisies à la ligne de commande
for arg in "$@"
do
# Vérifier si largument existe
if test -e "$arg"
then

# récuperer dans une variable les droits en octal (Bonus Partie 1) 
permissionProprietaire='+'$(ls -ld $arg | cut -c 2-4 | sed 's/-//g')
permissionGroupe='+'$(ls -ld $arg | cut -c 5-7 | sed 's/-//g')
permissionUser='+'$(ls -ld $arg | cut -c 8-10 | sed 's/-//g')
droit=$permissionProprietaire$permissionGroupe$permissionUser

# tester si largument est un fichier régulier
if test -f "$arg" 
then

# décoder le fichier encodé en préalable qu'on ajoute ensuite à larchive my-ball
cat  << fin >> my-ball.sh     
\`./DECODAGE << fini >> "$arg"
`./ENCODAGE "$arg" < "$arg"`
fini\`
chmod $droit "$arg" # donner les droits initiaux au fichier décodé
fin
elif test -d "$arg" # vérifier si largument est un répertoire
then
cat << DIR >> my-ball.sh # redirectionner le contenu vers larchive my-ball
mkdir -p "$arg" # elle crée un répertore
chmod $droit "$arg" # donner les droits daccés au répertoire
DIR
for i in $arg/* # une boucle qui parcoure les fichiers et les sous-répertoire du répertoire courant
do
if test -f $i # vérifier si les arguments du répertoire sont des fichier réguliers
then
permissionProprietaire2='+'$(ls -l $i | cut -c 2-4 | sed 's/-//g')
permissionGroupe2='+'$(ls -l $i | cut -c 5-7 | sed 's/-//g')
permissionUser2='+'$(ls -l $i | cut -c 8-10 | sed 's/-//g')
droit=$permissionProprietaire2$permissionGroupe2$permissionUser2 # récuperer dans une variable  les droits daccés à ses fichier
cat  << fin >> my-ball.sh
\`./DECODAGE << fini >> "$i"
`./ENCODAGE "$i" < "$i"`
fini\`
chmod $droit "$i" # donner les droits daccés à ses fichiers
fin
elif test -d $i # tester si les sous-arguments sont aussi des répertoires
then
  $0 $i  # faire la récursivité sur les fichiers et sous-répertoires
fi
done
fi
fi
done
chmod u+x my-ball.sh # donner les droits daccés à larchive my-ball
