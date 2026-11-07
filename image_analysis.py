"""

Запуск:
    python image_analysis.py              # создаст тестовое изображение
    python image_analysis.py photo.jpg    # проанализирует файл

Перед запуском:
    pip install pillow numpy matplotlib
"""

import sys

import numpy as np
import matplotlib.pyplot as plt
from PIL import Image, ImageDraw, ImageFilter


def create_test_image(width=400, height=300):
    """Создаёт тестовое изображение: цветной градиент + несколько фигур."""
    x = np.linspace(0, 255, width)
    y = np.linspace(0, 255, height)
    xx, yy = np.meshgrid(x, y)

    arr = np.zeros((height, width, 3), dtype=np.uint8)
    arr[:, :, 0] = xx # красный растёт слева направо
    arr[:, :, 1] = yy # зелёный растёт сверху вниз
    arr[:, :, 2] = 255 - xx # синий убывает слева направо

    img = Image.fromarray(arr, "RGB")
    draw = ImageDraw.Draw(img)
    draw.rectangle([50, 50, 150, 150], fill=(255, 255, 255))
    draw.ellipse([220, 80, 340, 200], fill=(0, 0, 0))
    draw.polygon([(100, 270), (180, 180), (260, 270)], fill=(255, 255, 0))
    return img


def main():
    # 2. Открываем файл или создаём тестовое изображение
    if len(sys.argv) > 1:
        img = Image.open(sys.argv[1]).convert("RGB")
        print(f"Открыт файл: {sys.argv[1]}")
    else:
        img = create_test_image()
        print("Файл не указан — создано тестовое изображение")

    # 3. Размер и число пикселей
    width, height = img.size
    print(f"\nШирина: {width} px")
    print(f"Высота: {height} px")
    print(f"Всего пикселей: {width * height}")

    # 4. Статистика по каналам R, G, B
    arr = np.array(img)
    print("\nСтатистика по каналам:")
    for i, name in enumerate(["Красный", "Зелёный", "Синий"]):
        ch = arr[:, :, i]
        print(f"  {name:8}: среднее = {ch.mean():6.2f}, "
              f"мин = {ch.min():3}, макс = {ch.max():3}")

    # 5. Оттенки серого и средняя яркость (0 — чёрный, 255 — белый)
    gray = img.convert("L")
    gray_arr = np.array(gray)
    print(f"\nСредняя яркость (0–255): {gray_arr.mean():.2f}")

    # 6. Поиск границ фильтром
    edges = gray.filter(ImageFilter.FIND_EDGES)

    # 7. Четыре графика в одном окне
    fig, axes = plt.subplots(2, 2, figsize=(10, 8))

    axes[0, 0].imshow(img)
    axes[0, 0].set_title("Исходное изображение")

    axes[0, 1].imshow(gray, cmap="gray")
    axes[0, 1].set_title("Оттенки серого")

    axes[1, 0].imshow(edges, cmap="gray")
    axes[1, 0].set_title("Границы (FIND_EDGES)")

    for i, color in enumerate(["red", "green", "blue"]):
        axes[1, 1].hist(arr[:, :, i].ravel(), bins=256, range=(0, 255),
                        color=color, alpha=0.5, label=color)
    axes[1, 1].set_title("Гистограмма цветов")
    axes[1, 1].set_xlabel("Значение пикселя")
    axes[1, 1].set_ylabel("Количество")
    axes[1, 1].legend()

    for ax in (axes[0, 0], axes[0, 1], axes[1, 0]):
        ax.axis("off")

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
