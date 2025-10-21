import os
import matplotlib.pyplot as plt

DATA_DIR = "../results"
FILES = ["VertexTest_2_Kruskal.txt", "VertexTest_2_Prim.txt"]
OUTPUT_FILE = "combined_plot_vertex_test_3.png"

plt.figure(figsize=(8, 6))

for filename in FILES:
    filepath = os.path.join(DATA_DIR, filename)
    if not os.path.exists(filepath):
        print(f"⚠️ Файл {filename} не найден, пропускаю.")
        continue

    x_values = []
    y_values = []
    with open(filepath, "r", encoding="utf-8") as f:
        for line in f:
            parts = line.strip().replace(",", " ").split()
            if len(parts) < 4:
                continue
            try:
                a = float(parts[0])
                b = float(parts[1])
                c = float(parts[2])
                x_values.append(a + b)
                y_values.append(c)
            except ValueError:
                continue

    if not x_values:
        print(f"⚠️ Файл {filename} пуст или некорректен.")
        continue

    plt.plot(
        x_values,
        y_values,
        marker='o',
        linestyle='-',
        linewidth=1.5,
        markersize=3,
        label=filename
    )

plt.title("Сравнение данных из двух файлов")
plt.xlabel("|V| + |E|")
plt.ylabel("T(n)")
plt.grid(True)
plt.legend()
plt.tight_layout()

os.makedirs("plots", exist_ok=True)
output_path = os.path.join("plots", OUTPUT_FILE)
plt.savefig(output_path, dpi=200)
plt.close()

print(f"✅ График успешно сохранён: {output_path}")
