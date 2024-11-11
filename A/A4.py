import tkinter as tk
from tkinter import messagebox

def encrypt_text():
    try:
        plaintext = entry_plaintext.get()
        key = int(entry_key.get())
        
        if not plaintext:
            messagebox.showwarning("Warning", "Please enter plaintext!")
            return

        ciphertext = ''.join(chr(ord(char) + key) for char in plaintext)
        label_ciphertext["text"] = f"Ciphertext: {ciphertext}"
    except ValueError:
        messagebox.showerror("Error", "Key must be an integer.")

# Create GUI
window = tk.Tk()
window.title("Encryption Program")
window.geometry("400x250")

# Plaintext input
label_plaintext = tk.Label(window, text="Enter Plaintext (M):", font=("Arial", 12))
label_plaintext.pack(pady=5)
entry_plaintext = tk.Entry(window, font=("Arial", 12), width=30)
entry_plaintext.pack(pady=5)

# Key input
label_key = tk.Label(window, text="Enter Key (K):", font=("Arial", 12))
label_key.pack(pady=5)
entry_key = tk.Entry(window, font=("Arial", 12), width=10)
entry_key.pack(pady=5)

# Encrypt button
button_encrypt = tk.Button(window, text="Encrypt", command=encrypt_text, font=("Arial", 12))
button_encrypt.pack(pady=10)

# Ciphertext output
label_ciphertext = tk.Label(window, text="Ciphertext: ", font=("Arial", 12))
label_ciphertext.pack(pady=5)

window.mainloop()
