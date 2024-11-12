import tkinter as tk
from tkinter import filedialog, messagebox

def open_file():
    file_path = filedialog.askopenfilename(defaultextension=".txt", filetypes=[("Text files", "*.txt"), ("All files", "*.*")])
    if file_path:
        try:
            with open(file_path, "r") as file:
                text_area.delete(1.0, tk.END)
                text_area.insert(tk.END, file.read())
            window.title(f"Text Editor - {file_path}")
        except Exception as e:
            messagebox.showerror("Error", f"Could not open file: {e}")

def save_file():
    file_path = filedialog.asksaveasfilename(defaultextension=".txt", filetypes=[("Text files", "*.txt"), ("All files", "*.*")])
    if file_path:
        try:
            with open(file_path, "w") as file:
                file.write(text_area.get(1.0, tk.END))
            window.title(f"Text Editor - {file_path}")
        except Exception as e:
            messagebox.showerror("Error", f"Could not save file: {e}")

# Create GUI
window = tk.Tk()
window.title("Text Editor")
window.geometry("600x400")

# Text area for editing
text_area = tk.Text(window, wrap="word", font=("Arial", 12))
text_area.pack(expand=True, fill="both")

# Menu bar
menu_bar = tk.Menu(window)
window.config(menu=menu_bar)

# File menu
file_menu = tk.Menu(menu_bar, tearoff=0)
file_menu.add_command(label="Open", command=open_file)
file_menu.add_command(label="Save", command=save_file)
file_menu.add_separator()
file_menu.add_command(label="Exit", command=window.quit)
menu_bar.add_cascade(label="File", menu=file_menu)

window.mainloop()
