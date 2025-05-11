# Encodeur-Décodeur

## Description

Ce projet contient des programmes en C destinés à l'encodage et au décodage de données. Il inclut des scripts shell facilitant l'intégration et la génération automatique d'exemples de tests.

## Structure du Projet

Le projet est organisé comme suit :

```
Encodeur_Decodeur/
├── encodeur               # Exécutable encodeur
├── decodeur               # Exécutable décodeur
├── encodeur.c             # Code source de l'encodeur
├── decodeur.c             # Code source du décodeur
├── filtreEncodeur.c       # Code source du filtre d'encodage
├── filtreDecodage.c       # Code source du filtre de décodage
├── integration.sh         # Script pour intégrer les composants
├── ENCODAGE               # Fichier ou répertoire lié à l'encodage
├── DECODAGE               # Fichier ou répertoire lié au décodage
├── create-ball.sh         # Script shell pour créer un exemple de balle
└── create5-ball.sh        # Script shell pour créer 5 exemples de balles
```

## Fonctionnalités

* **Encodage de données :** Transforme des données brutes en format encodé.
* **Décodage de données :** Récupère les données originales depuis le format encodé.
* **Scripts de génération :** Fournissent des exemples automatisés pour tester rapidement les fonctionnalités.
* **Intégration automatisée :** Un script facilite l'intégration des différentes parties du projet.

## Instructions d'utilisation

### Compilation

Pour compiler les programmes, utilisez les commandes suivantes :

```bash
gcc -o encodeur encodeur.c filtreEncodeur.c
gcc -o decodeur decodeur.c filtreDecodage.c
```

### Exécution

Pour utiliser les exécutables générés :

Encodage :

```bash
./encodeur < fichier_source > fichier_encodé
```

Décodage :

```bash
./decodeur < fichier_encodé > fichier_décodé
```

### Scripts de génération d'exemples

Créer un exemple :

```bash
./create-ball.sh
```

Créer cinq exemples :

```bash
./create5-ball.sh
```

### Intégration automatisée

Pour automatiser l'intégration du projet, exécutez :

```bash
./integration.sh
```

## Prérequis

* Compilateur `gcc`
* Shell Unix/Linux

## Auteur

Votre Nom - Votre Email

## Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

---

**[KECHIR Amine](https://github.com/amn-kchr)**
