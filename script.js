let students = [];

const SERVER = "http://127.0.0.1:8080";

function showSection(sectionId) {
    document.querySelectorAll(".section").forEach(section => {
        section.classList.remove("active");
    });

    document.getElementById(sectionId).classList.add("active");

    let titles = {
        dashboard: "Dashboard",
        students: "Student Records",
        analysis: "Data Analysis",
        optimization: "Optimization Lab"
    };

    document.querySelector(".topbar h1").textContent = titles[sectionId];
}

document.getElementById("studentForm").addEventListener("submit", async function(event) {
    event.preventDefault();

    let id = Number(document.getElementById("studentId").value);
    let name = document.getElementById("studentName").value.trim();
    let department = document.getElementById("studentDepartment").value;
    let marks = Number(document.getElementById("studentMarks").value);

    if (marks < 0 || marks > 100) {
        alert("Marks must be between 0 and 100.");
        return;
    }

    try {
        let response = await fetch(SERVER + "/add", {
            method: "POST",
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            },
            body: "id=" + id +
                  "&name=" + name +
                  "&department=" + department +
                  "&marks=" + marks
        });

        if (!response.ok) {
            throw new Error("Server error");
        }

        students.push({
            id: id,
            name: name,
            department: department,
            marks: marks
        });

        displayStudents();
        updateDashboard();

        document.getElementById("studentForm").reset();

        alert("Student added successfully!");
    }
    catch (error) {
        alert("C++ backend not connected.");
    }
});

function getGrade(marks) {
    if (marks >= 90) return "A+";
    if (marks >= 80) return "A";
    if (marks >= 70) return "B";
    if (marks >= 50) return "C";
    return "F";
}

function displayStudents(data = students) {
    let table = document.getElementById("studentTableBody");

    table.innerHTML = "";

    data.forEach(student => {
        table.innerHTML += `
            <tr>
                <td>${student.id}</td>
                <td>${student.name}</td>
                <td>${student.department}</td>
                <td>${student.marks}</td>
                <td>${getGrade(student.marks)}</td>
                <td>${student.marks >= 50 ? "Pass" : "Fail"}</td>
                <td>
                    <button onclick="deleteStudent(${student.id})">
                        Delete
                    </button>
                </td>
            </tr>
        `;
    });
}

function deleteStudent(id) {
    students = students.filter(student => student.id !== id);

    displayStudents();
    updateDashboard();
}

function searchStudents() {
    let search = document.getElementById("searchInput").value.toLowerCase();

    let result = students.filter(student =>
        student.name.toLowerCase().includes(search) ||
        student.id.toString().includes(search) ||
        student.department.toLowerCase().includes(search)
    );

    displayStudents(result);
}

function updateDashboard() {
    let total = students.length;

    document.getElementById("totalStudents").textContent = total;

    if (total === 0) {
        document.getElementById("averageMarks").textContent = "0";
        document.getElementById("highestMarks").textContent = "0";
        document.getElementById("passPercentage").textContent = "0%";
        document.getElementById("analysisTotal").textContent = "0";
        document.getElementById("analysisAverage").textContent = "0";
        document.getElementById("analysisHighest").textContent = "0";
        document.getElementById("analysisLowest").textContent = "0";
        return;
    }

    let totalMarks = 0;
    let highest = students[0].marks;
    let lowest = students[0].marks;
    let passed = 0;

    students.forEach(student => {
        totalMarks += student.marks;

        if (student.marks > highest)
            highest = student.marks;

        if (student.marks < lowest)
            lowest = student.marks;

        if (student.marks >= 50)
            passed++;
    });

    let average = totalMarks / total;

    document.getElementById("averageMarks").textContent =
        average.toFixed(1);

    document.getElementById("highestMarks").textContent =
        highest;

    document.getElementById("passPercentage").textContent =
        ((passed / total) * 100).toFixed(0) + "%";

    document.getElementById("analysisTotal").textContent =
        total;

    document.getElementById("analysisAverage").textContent =
        average.toFixed(1);

    document.getElementById("analysisHighest").textContent =
        highest;

    document.getElementById("analysisLowest").textContent =
        lowest;
}

function linearSearch(id) {
    for (let student of students) {
        if (student.id === id)
            return student;
    }

    return null;
}

function binarySearch(id) {
    let data = [...students].sort((a, b) => a.id - b.id);

    let left = 0;
    let right = data.length - 1;

    while (left <= right) {
        let middle = Math.floor((left + right) / 2);

        if (data[middle].id === id)
            return data[middle];

        if (data[middle].id < id)
            left = middle + 1;
        else
            right = middle - 1;
    }

    return null;
}

function runSearch() {
    let id = Number(
        document.getElementById("optimizationSearchInput").value
    );

    let linear = linearSearch(id);
    let binary = binarySearch(id);

    if (linear) {
        document.getElementById("linearResult").textContent =
            "Found: " + linear.name;

        document.getElementById("binaryResult").textContent =
            "Found: " + binary.name;

        document.getElementById("optimizationResult").textContent =
            "Student found using both algorithms.";
    }
    else {
        document.getElementById("linearResult").textContent =
            "Student not found";

        document.getElementById("binaryResult").textContent =
            "Student not found";

        document.getElementById("optimizationResult").textContent =
            "No student found.";
    }
}

displayStudents();
updateDashboard();