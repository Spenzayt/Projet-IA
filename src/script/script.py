from PIL import Image

def convert_image_to_map(image_path, output_path):
    # Ouvre l'image
    img = Image.open(image_path)

    # Convertit l'image en niveaux de gris (si ce n'est pas déjà fait)
    img = img.convert('1')  # '1' signifie mode binaire: noir et blanc
    
    # Récupère les pixels
    pixels = img.load()
    
    # Ouvre un fichier pour écrire la carte
    with open(output_path, 'w') as file:
        for y in range(img.height):
            row = ''
            for x in range(img.width):
                if pixels[x, y] == 255:  # 255 est blanc
                    row += '0'  # Remplace le blanc par un 0
                else:
                    row += '1'  # Remplace le noir par un 1
            file.write(row + '\n')

    print(f"Map saved to {output_path}")

# Exemple d'utilisation
image_path = 'map.png'  # Remplace par le chemin de ton image
output_path = 'output_map.txt'  # Remplace par le chemin de sortie pour la carte
convert_image_to_map(image_path, output_path)
