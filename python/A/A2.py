import random
import string
import tkinter as tk
from tkinter import messagebox

def generate_random_string():
    length = random.randint(5, 15)  # Random length between 5 and 15 characters
    return ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(length))

def calculate_accuracy(generated, user_input):
    correct_count = sum(1 for i, j in zip(generated, user_input) if i == j)
    return correct_count / max(len(generated), len(user_input)) * 100

def start_typing_test():
    global generated_string
    generated_string = generate_random_string()
    label_string["text"] = f"Type this: {generated_string}"
    entry_input.delete(0, tk.END)

def check_accuracy():
    user_input = entry_input.get()
    if not user_input:
        messagebox.showwarning("Warning", "Input cannot be empty!")
        return
    
    accuracy = calculate_accuracy(generated_string, user_input)
    messagebox.showinfo("Result", f"Accuracy: {accuracy:.2f}%")

# Create GUI
window = tk.Tk()
window.title("Typing Test Program")
window.geometry("400x200")

label_string = tk.Label(window, text="Click 'Start' to generate a random string", font=("Arial", 14))
label_string.pack(pady=10)

entry_input = tk.Entry(window, font=("Arial", 14), width=30)
entry_input.pack(pady=10)

button_start = tk.Button(window, text="Start", command=start_typing_test, font=("Arial", 12))
button_start.pack(pady=5)

button_check = tk.Button(window, text="Check Accuracy", command=check_accuracy, font=("Arial", 12))
button_check.pack(pady=5)

window.mainloop()
