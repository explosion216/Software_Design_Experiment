import tkinter as tk
from tkinter import messagebox

# List to store students' names and scores
students = []

def add_student():
    name = entry_name.get().strip()
    try:
        score = int(entry_score.get().strip())
        if name and score >= 0:
            students.append((name, score))
            entry_name.delete(0, tk.END)
            entry_score.delete(0, tk.END)
            messagebox.showinfo("Success", f"Added {name} with score {score}")
        else:
            messagebox.showwarning("Warning", "Please enter a valid name and score.")
    except ValueError:
        messagebox.showerror("Error", "Score must be an integer.")

def display_sorted_scores():
    if not students:
        messagebox.showinfo("Info", "No students added yet.")
        return

    # Sort students by score in descending order
    sorted_students = sorted(students, key=lambda x: x[1], reverse=True)
    
    # Display sorted scores
    result_text = "\n".join([f"{name}: {score}" for name, score in sorted_students])
    result_label["text"] = f"Sorted Scores:\n{result_text}"

# GUI setup
window = tk.Tk()
window.title("Student Score Statistics")
window.geometry("400x300")

# Name input
label_name = tk.Label(window, text="Student Name:", font=("Arial", 12))
label_name.pack(pady=5)
entry_name = tk.Entry(window, font=("Arial", 12), width=30)
entry_name.pack(pady=5)

# Score input
label_score = tk.Label(window, text="Score:", font=("Arial", 12))
label_score.pack(pady=5)
entry_score = tk.Entry(window, font=("Arial", 12), width=30)
entry_score.pack(pady=5)

# Buttons for adding and displaying sorted scores
button_add = tk.Button(window, text="Add Student", command=add_student, font=("Arial", 12))
button_add.pack(pady=10)

button_display = tk.Button(window, text="Display Sorted Scores", command=display_sorted_scores, font=("Arial", 12))
button_display.pack(pady=10)

# Label to show sorted results
result_label = tk.Label(window, text="Sorted Scores will appear here", font=("Arial", 12), justify="left")
result_label.pack(pady=10)

window.mainloop()

