<?php

$FIREBASE = "https://tracker-55a0c.firebaseio.com/";	
$NODE_PATCH = "locations/537.json";			
$LAT = $_GET["lat"];					
$LON = $_GET["lon"];


if($LAT==null || $LON==null){
    echo "data not to be null";
    return;
}

$data = 32;

$data = array(
    "lat" => $LAT,
    "lon" => $LON
);


$json = json_encode( $data );

$curl = curl_init();

curl_setopt( $curl, CURLOPT_URL, $FIREBASE . $NODE_PATCH );
curl_setopt( $curl, CURLOPT_CUSTOMREQUEST, "PATCH" );
curl_setopt( $curl, CURLOPT_POSTFIELDS, $json );
curl_setopt( $curl, CURLOPT_RETURNTRANSFER, true );


$response = curl_exec( $curl );
curl_close( $curl );

echo $response . "\n";

?>