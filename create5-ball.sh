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
if test -f "$arg" # verifier si largument est un fichier régulier
then
cat << fin >> my-ball.sh # ajouter le contenu de largument et la  sortie standard à larchive my-ball
cat << - > "$arg" # afficher le contenu de largument
$(sed -e 's/\$/\\$/g' -e 's/`/\\`/g' "$arg")
-
fin
# utilisation une expression régulière pour substituer les caractères non-imprémable par des caracteres imprémables (sed)
elif test -d "$arg" # vérifier si largument est un répertoire
then
cat << DIR >> my-ball.sh # redirectionner le contenu vers larchive my-ball
mkdir -p "$arg" # elle crée un répertore
DIR
for i in $arg/* # une boucle qui parcoure les fichiers et les sous-répertoire du répertoire courant
do
if test -f $i # vérifier si les arguments du répertoire sont des fichier réguliers
then
cat << fin >> my-ball.sh
cat << - > "$i"
$(sed -e 's/\$/\\$/g' -e 's/`/\\`/g' "$i")
-
fin
# utilisation une expression régulière pour substituer les caractères non-imprémable par des caracteres imprémables(sed)
elif test -d $i # tester si les sous-arguments sont aussi des répertoires
then
  $0 $i  # faire la récursivité sur les fichiers et sous-répertoires
fi
done
fi
fi
done
chmod u+x my-ball.sh # donner les droits daccés à larchive my-ball
