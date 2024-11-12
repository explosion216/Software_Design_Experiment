import tkinter as tk
from tkinter import messagebox

def convert_number():
    try:
        number = entry_number.get()
        base = base_var.get()

        if base == "Binary":
            decimal_value = int(number, 2)
        elif base == "Octal":
            decimal_value = int(number, 8)
        elif base == "Decimal":
            decimal_value = int(number, 10)
        elif base == "Hexadecimal":
            decimal_value = int(number, 16)
        else:
            raise ValueError("Invalid base selected.")

        binary_result.set(bin(decimal_value)[2:])
        octal_result.set(oct(decimal_value)[2:])
        decimal_result.set(str(decimal_value))
        hex_result.set(hex(decimal_value)[2:].upper())

    except ValueError:
        messagebox.showerror("Error", "Invalid input for the selected base.")

# GUI setup
window = tk.Tk()
window.title("Base Converter")
window.geometry("400x410")

# Input field for the number
label_number = tk.Label(window, text="Enter Number:", font=("Arial", 12))
label_number.pack(pady=5)
entry_number = tk.Entry(window, font=("Arial", 12), width=30)
entry_number.pack(pady=5)

# Base selection dropdown
label_base = tk.Label(window, text="Select Base:", font=("Arial", 12))
label_base.pack(pady=5)

base_var = tk.StringVar(value="Decimal")
base_options = ["Binary", "Octal", "Decimal", "Hexadecimal"]
dropdown_base = tk.OptionMenu(window, base_var, *base_options)
dropdown_base.pack(pady=5)

# Convert button
button_convert = tk.Button(window, text="Convert", command=convert_number, font=("Arial", 12))
button_convert.pack(pady=10)

# Output fields
binary_result = tk.StringVar()
octal_result = tk.StringVar()
decimal_result = tk.StringVar()
hex_result = tk.StringVar()

label_binary = tk.Label(window, text="Binary:", font=("Arial", 12))
label_binary.pack()
entry_binary = tk.Entry(window, font=("Arial", 12), textvariable=binary_result, state="readonly", width=30)
entry_binary.pack(pady=2)

label_octal = tk.Label(window, text="Octal:", font=("Arial", 12))
label_octal.pack()
entry_octal = tk.Entry(window, font=("Arial", 12), textvariable=octal_result, state="readonly", width=30)
entry_octal.pack(pady=2)

label_decimal = tk.Label(window, text="Decimal:", font=("Arial", 12))
label_decimal.pack()
entry_decimal = tk.Entry(window, font=("Arial", 12), textvariable=decimal_result, state="readonly", width=30)
entry_decimal.pack(pady=2)

label_hex = tk.Label(window, text="Hexadecimal:", font=("Arial", 12))
label_hex.pack()
entry_hex = tk.Entry(window, font=("Arial", 12), textvariable=hex_result, state="readonly", width=30)
entry_hex.pack(pady=2)

window.mainloop()
