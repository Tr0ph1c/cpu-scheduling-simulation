<?php
$inputs_file = fopen("inputs", "w") or die("cant open inputs");
$outputs_file = fopen("outputs", "r") or die("cant open outputs");



// SET VARIABLES
$NOP = 1;
$QT = 10;

if($_SERVER['REQUEST_METHOD'] === 'GET' &&
isset($_REQUEST["NOPvar"]) &&
isset($_REQUEST["QTvar"])) 
{
    $QT = $_REQUEST["QTvar"];
    $NOP = $_REQUEST["NOPvar"];
    
    fwrite($inputs_file, $_GET["QTvar"]."\n");
    fwrite($inputs_file, $_GET["NOPvar"]."\n");

    for ($i = 0; $i < intval($NOP); $i++) {
        if (isset($_GET["P${i}BT"])) fwrite($inputs_file, $_GET["P${i}BT"]."\n");
        if (isset($_GET["P${i}AT"])) fwrite($inputs_file, $_GET["P${i}AT"]."\n");
    }
}
// END SET VARIABLES


// GET ALL OUTPUTS FROM OUTPUTS FILE
$raw_arr = array();
while (!feof($outputs_file)) {
    array_push($raw_arr, fgets($outputs_file));
}
// END GET ALL OUTPUTS FROM OUTPUTS FILE


fclose($inputs_file);
fclose($outputs_file);
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Round Robin Scheduling Algorithm Simulation</title>
        <link rel="stylesheet" href="style.css">
        <link rel="icon" href="./imgs/icon.ico">
    </head>

    <body>
        <div class="container">
            <div class="section" id="description">
                <div class="description">
                    <h1>Round Robin Scheduling Algorithm</h1>
                    <p>Round Robin is a preemptive scheduling algorithm designed for time-sharing systems...</p>
                    <h2><span class="A">A</span>dvantages:</h2>
                    <ul>
                        <li>Fairness: Ensures that each process gets an equal share of CPU time.</li>
                        <li>Preemptive: Allows multiple processes to execute concurrently.</li>
                        <li>Simple Implementation: Easy to understand and implement.</li>
                    </ul>
                    <h2><span class="D">Dis</span>advantages:</h2>
                    <ul>
                        <li>Overhead: Can lead to high context switch overhead, especially with small time quanta.</li>
                        <li>Poor Performance: May not perform well for long-running processes or when the time quantum is too short.</li>
                    </ul>
                </div>
            </div>

            <div class="section" id="table">
                <div class="preq">
                    <div class="inp-box">
                        <label for="QT">Quantum time (ms): </label>
                        <input type="number" id="QT" min="1" max="1000" step="1" onchange="setQT();" value="<?php echo $QT; ?>">
                    </div>
    
                    <div class="inp-box">
                        <label for="NOP">Number of processes: </label>
                        <input type="number" id="NOP" min="1" max="100" step="1" onchange="changeNOP();" value=<?php echo $NOP ?>>
                    </div>
                </div>

                <table>
                    <tbody>
                        <tr>
                            <th>PID</th>
                            <th>BT</th>
                            <th>AT</th>
                            <th>CT</th>
                            <th>WT</th>
                            <th>TT</th>
                            <th>RT</th>
                        </tr>
                    </tbody>
                </table>
                <form action="index.php" method="get">
                    <?php
                    if($_SERVER['REQUEST_METHOD'] === 'GET' && count($raw_arr) != 0) {
                        $num_of_rows = $NOP;
                        echo '<table id="s">';
                        for ($i=0; $i < $num_of_rows; $i++) {

                            echo '<tr>';
                            echo "<td>P{$i}</td>";
                            echo "<td class=edit><input class='input-td' type=number name='P${i}BT' value=";
                            echo $_GET["P${i}BT"];
                            echo "></td>";
                            echo "<td class=edit><input class='input-td' type=number name='P${i}AT' value=";
                            echo $_GET["P${i}AT"];
                            echo "></td>";
                            echo "<td id='CT${i}'></td>";
                            echo "<td id='WT${i}'></td>";
                            echo "<td id='TT${i}'></td>";
                            echo "<td id='RT${i}'></td>";
                            echo '</tr>';
                        }
                        echo '</table>';
                    } else {
                        echo '<table id="s"></table>';
                    }
                    ?>
    
                    <button style="margin-top: 10px;" id="btn">Start Simulation</button>
                    <input type="hidden" id="NOPvar" name="NOPvar"/>
                    <input type="hidden" id="QTvar" name="QTvar"/>
                </form>
            </div>

            <div class="section" id="gantt">
                <h1>GANTT CHART</h1>
            </div>
        </div>

        <div class="BG"></div>
    </body>

    <script>
        setNOP();
        setQT();

        let NOP = document.getElementById("NOP");
        let QT = document.getElementById("QT");

        function changeNOP() {
            let x = parseInt(document.getElementById("NOP").value);
            let NOPvar = document.getElementById("NOPvar");
            NOPvar.value=x;

            let y = "";

            for(let i = 0; i < x; i++) {
                y += "<tr>";
                    y += `<td>P${i}</td>`;
                    y += `<td class=edit><input class='input-td' type=number name="P${i}BT"></td>`;
                    y += `<td class=edit><input class='input-td' type=number name="P${i}AT"></td>`;
                    y += `<td id="CT${i}"></td>`;
                    y += `<td id="WT${i}"></td>`;
                    y += `<td id="TT${i}"></td>`;
                    y += `<td id="RT${i}"></td>`;
                y += "</tr>";
            }

            try {
                document.getElementById("s").innerHTML = y;
            } catch (error) {
                console.log("js table element disabled <= setNOP()");
            }
        }
        
        function setNOP() {
            let x = parseInt(document.getElementById("NOP").value);
            let NOPvar = document.getElementById("NOPvar");
            NOPvar.value=x;
        }

        function setQT() {
            let x = parseInt(document.getElementById("QT").value);
            let QTvar = document.getElementById("QTvar");
            QTvar.value=x;
        }
    </script>
</html>


