<?php

$dir = "/arquivos/programas/stargus/stargus/svn/stargus/data";

function clean($dir) {
	//echo "diretorio - $dir\n";
	// Open a known directory, and proceed to read its contents
	if (is_dir($dir)) {
		if ($dh = opendir($dir)) {
			while (($file = readdir($dh)) !== false) {
				if (is_file($dir."/".$file)) {
					if  (strstr($file, ".lua")) {
						echo "nao apagando lua script '$file'\n";
					} else {
						echo "apagando " . $dir ."/". $file . "\n";
						unlink($dir ."/". $file);
					}
				} else if (is_dir($dir."/".$file) AND $file != "." AND $file != "..") {
					clean($dir."/".$file);
				} else {
					//echo "não entrando em '$file'\n";
				}
			}
			closedir($dh);
		}
	}
}


clean($dir);

?>