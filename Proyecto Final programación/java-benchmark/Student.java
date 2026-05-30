public class Student {

    int student_id;
    String full_name;
    String career;
    int semester;
    double gpa;
    int skill_score;

    public Student(
            int student_id,
            String full_name,
            String career,
            int semester,
            double gpa,
            int skill_score) {

        this.student_id = student_id;
        this.full_name = full_name;
        this.career = career;
        this.semester = semester;
        this.gpa = gpa;
        this.skill_score = skill_score;
    }

    @Override
    public String toString() {

        return
                "ID: " + student_id +
                        " | Nombre: " + full_name +
                        " | Carrera: " + career +
                        " | Semestre: " + semester +
                        " | GPA: " + gpa +
                        " | Skill: " + skill_score;
    }
}