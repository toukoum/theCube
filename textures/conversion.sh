#!/bin/bash

# Vérifiez si le dossier "convert" existe
if [ ! -d "convert" ]; then
  echo "Le dossier 'convert' n'existe pas."
  exit 1
fi

# Compteur pour nommer les fichiers séquentiellement
counter=1

# Parcourir tous les fichiers PNG dans le dossier "convert"
for img in convert/*.png; do
  # Vérifiez si des fichiers PNG existent
  if [ ! -f "$img" ]; then
    echo "Aucun fichier PNG trouvé dans le dossier 'convert'."
    exit 1
  fi
  
  # Convertir l'image PNG en XPM
  convert "$img" "convert/$counter.xpm"
  
  # Incrémenter le compteur
  counter=$((counter + 1))
done

echo "Conversion terminée. $((counter - 1)) fichiers convertis."
