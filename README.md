# Projet 2 HAI716I 2026 - DOMBROWSKI Tahina
Dépot Github du projet 2 de l'UE HAI716I 2026

Langage : C++

## Compiler

```
g++ main.cpp StratPlayer.cpp -o projet2
```

## Lancer la simulation

```
./projet2 <choix du format> <affichage ou non des tours>
```

FOUR-T contre tous sans affichage des résultats de tours :

```
./projet2 ft
```

FOUR-T contre tous avec affichage des résultats de tours :

```
./projet2 ft print_turns
```

Tournoi Axelrod sans FOUR-T et ALTERNATOR-C, sans affichage des résultats de tours :

```
./projet2 axelrod_base
```

Tournoi Axelrod sans FOUR-T et ALTERNATOR-C avec affichage des résultats de tours :

```
./projet2 axelrod_base print_turns
```

Tournoi Axelrod sans affichage des résultats de tours :

```
./projet2 axelrod
```

Tournoi Axelrod avec affichage des résultats de tours :

```
./projet2 axelrod print_turns
```
