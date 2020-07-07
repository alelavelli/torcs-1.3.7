- Makefile, human.cpp, human.h, human.xml, human_sensors.cpp e human_sensors.h in    src/drivers/human/
- rttelem.cpp in              src/libs/robottools/
- telemetry.cpp in            src/modules/telemetry/

Per raccogliere i dati: practice con driver non scr_sever ma player.
Creare cartella /home/UTENTE/raw_torcs_data/ perché i file vengono salvati anche qua
Il csv con i dati salvati lo troverai qui: /usr/local/share/games/torcs/telemetry.

Per estrarre le features Ferrari dai dati grezzi di TORCS usare i file: 'preprocess_raw_torcs.py' e poi 'build_dataset_offroad.py'

Per salvare più giri bisogna modificare riga 1033 'src/drivers/human/human.cpp'

Ad esempio, per salvare 2 giri bisogna mettere:
if (car->_laps == 3) {
​           if (HCtx[idx]->lap == 2) {

Per modificare la frequenza di campionamento nel file raceman.h:
#define RCM_MAX_DT_ROBOTS	0.0099 // 100Hz
