# Projet 2 HAI716I 2026 - DOMBROWSKI Tahina
Dépot Github du projet 2 de l'UE HAI716I 2026

Langage : C++

## Compiler

```
g++ main.cpp StratPlayer.cpp -o projet2
```

## Lancer la simulation

Sans l'affichage des tours :

```
./projet2 <choix du format>
```

Avec l'affichage des tours :

```
./projet2 <choix du format> print_turns
```

choix du format : ft - axelrod_base - axelrod - axelrod_bruit - axelrod_horizon_inconnu

### Exemples :

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

Tournoi Axelrod avec probabilité d'inversion de coup de 5%, sans affichage des résultats de tours :

```
./projet2 axelrod_bruit
```

Tournoi Axelrod avec probabilité d'inversion de coup de 5%, avec affichage des résultats de tours :

```
./projet2 axelrod_bruit print_turns
```

Tournoi Axelrod avec probabilité de continuer une partie de 95%, sans affichage des résultats de tours :

```
./projet2 axelrod_horizon_inconnu
```

Tournoi Axelrod avec probabilité de continuer une partie de 95%, avec affichage des résultats de tours :

```
./projet2 axelrod_horizon_inconnu print_turns
```
