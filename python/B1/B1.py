import os

class Student:
    def __init__(self, student_id):
        self.student_id = student_id

    def get_id(self):
        return self.student_id

class StudentGrades(Student):
    ASSIGNMENT_WEIGHT = 0.3
    MIDTERM_WEIGHT = 0.3
    FINAL_WEIGHT = 0.4

    def __init__(self, student_id, assignment, midterm, final):
        super().__init__(student_id)
        self.assignment = assignment
        self.midterm = midterm
        self.final = final
        self.total_score = 0
        self.grade_level = ""

    def compute_total_score(self):
        self.total_score = (
            self.assignment * StudentGrades.ASSIGNMENT_WEIGHT +
            self.midterm * StudentGrades.MIDTERM_WEIGHT +
            self.final * StudentGrades.FINAL_WEIGHT
        )

    def compute_grade_level(self):
        if 90 <= self.total_score <= 100:
            self.grade_level = "A"
        elif 80 <= self.total_score < 90:
            self.grade_level = "B"
        elif 70 <= self.total_score < 80:
            self.grade_level = "C"
        elif 60 <= self.total_score < 70:
            self.grade_level = "D"
        else:
            self.grade_level = "E"

    def get_total_score(self):
        return self.total_score

    def get_grade_level(self):
        return self.grade_level

def read_students_from_file(filename):
    students = []
    with open(filename, "r") as file:
        student_count = int(file.readline().strip())
        for _ in range(student_count):
            line = file.readline().strip().split()
            student_id = line[0]
            assignment = float(line[1])
            midterm = float(line[2])
            final = float(line[3])
            student = StudentGrades(student_id, assignment, midterm, final)
            student.compute_total_score()
            student.compute_grade_level()
            students.append(student)
    return students

def calculate_class_average(students):
    total_score = sum(student.get_total_score() for student in students)
    return total_score / len(students) if students else 0

def classify_students(students):
    grade_counts = {"A": 0, "B": 0, "C": 0, "D": 0, "E": 0}
    for student in students:
        grade_counts[student.get_grade_level()] += 1
    total_students = len(students)
    percentages = {grade: (count / total_students * 100) for grade, count in grade_counts.items()}
    return grade_counts, percentages

def output_results(filename, students, class_average, grade_counts, percentages):
    with open(filename, "w") as file:
        file.write(f"Class Average Score: {class_average:.2f}\n\n")
        file.write("Student Results:\n")
        for student in students:
            file.write(f"{student.get_id()}    {student.get_total_score():.2f}    {student.get_grade_level()}\n")
        
        file.write("\nGrade Distribution:\n")
        for grade, count in grade_counts.items():
            file.write(f"{grade}: {count} students ({percentages[grade]:.2f}%)\n")

def main():
    input_file = "python/B1/note.dat"
    output_file = "python/B1/out.dat"
    if not os.path.exists(input_file):
        print("Input file not found.")
        return
    
    # Read student data from file
    students = read_students_from_file(input_file)
    
    # Calculate class average
    class_average = calculate_class_average(students)
    
    # Classify students into grade levels
    grade_counts, percentages = classify_students(students)
    
    # Output results
    output_results(output_file, students, class_average, grade_counts, percentages)
    print(f"Results have been saved to {output_file}")

if __name__ == "__main__":
    main()
