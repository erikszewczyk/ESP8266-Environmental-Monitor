<?php

    // Set device password. This must match the passcode in the Arduino code.
    $passcode = "[Device Passcode]";

// Check to see if the pass variable is there, if so assume they are trying to hit the device message endpoint
if(isset($_GET['pass']) && isset($_GET['device_name']) && ($_SERVER['SERVER_PORT'] == '80')){
    // Get values.
    $pass = $_GET['pass'];
    $device_name = $_GET['device_name'];
    if (isset($_GET['temperature'])) {
        $temperature = "'" . $_GET['temperature'] . "'";
    } else {
        $temperature = "NULL";
    }
    if (isset($_GET['humidity'])) {
        $humidity = "'" . $_GET['humidity'] . "'";
    } else {
        $humidity = "NULL";
    }
    if (isset($_GET['anvol'])) {
        $analog_voltage = "'" . $_GET['anvol'] . "'";
    } else {
        $analog_voltage = "NULL";
    }
    if (isset($_GET['distance'])) {
        $distance = "'" . $_GET['distance'] . "'";
    } else {
        $distance = "NULL";
    }
    date_default_timezone_set('America/Los_Angeles');
    $date= date('Y-m-d H:i:s');

    // Check if password is right. (If there is no password, assume no data is trying to be entered and skip over this.)
    if(isset($pass) && ($pass == $passcode)){
        // If all values are present, insert it into the MySQL database.
        if(isset($device_name) && isset($temperature) && isset($humidity)){
            // Database credentials
            $servername = "[MySQL Server]";
            $username = "[MySQL Username]";
            $dbname = "[MySQL DB Name]";
            $password = "[MySQL Password]";
            // Create connection.
            $conn = mysqli_connect($servername, $username, $password, $dbname);
            if (!$conn) {
                die("Connection failed: " . mysqli_connect_error());
            }

            // Insert values into table. Replace YOUR_TABLE_NAME with your database table name.
            $sql = "INSERT INTO YOUR_TABLE_NAME (datetime, device_name, temperature, humidity, analog_voltage, distance)
			    VALUES ('$date', '$device_name', $temperature, $humidity, $analog_voltage, $distance)";
            if (mysqli_query($conn, $sql)) {
                echo "OK";
            } else {
                echo "Fail: " . $sql . "<br/>" . mysqli_error($conn);
            }

            // Close connection.
            mysqli_close($conn);
        }
    }
} elseif(isset($_GET['pass']) && isset($_GET['transient_param']) && isset($_GET['state']) && ($_GET['pass'] == $passcode) && ($_SERVER['SERVER_PORT'] == '80')) {
    //Update transient state data
    $servername = "[MySQL Server]";
    $username = "[MySQL Username]";
    $dbname = "[MySQL Database]";
    $password = "[MySQL Passowrd]";
    // Create connection.
    $conn = mysqli_connect($servername, $username, $password, $dbname);
    if (!$conn) {
        die("Connection failed: " . mysqli_connect_error());
    }
    
    //Update record
    $newdate= date('Y-m-d H:i:s');
    $sql = "UPDATE transient_state SET last_update = '$newdate', state = '" . $_GET['state'] . "' WHERE param = '" . $_GET['transient_param'] . "'";
    if (mysqli_query($conn, $sql)) {
        echo "OK";
    } else {
        echo "Fail: " . $sql . "<br/>" . mysqli_error($conn);
    }

    // Close connection.
    mysqli_close($conn);
    
} else {
    // If they arent trying to hit the device message endpoint, then display the dashboard
    include "dashboard.php";
}
?>
