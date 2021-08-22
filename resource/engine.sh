export LD_LIBRARY_PATH=/usr/local/bin/
#/usr/bin/xfce4-terminal -T “scriptengine” -x bash -c “sh /usr/local/bin/engine_run.sh $1;exec bash;”
#PARAM='sh /usr/local/bin/engine_run.sh '$1';exec bash;'
PARAM='/usr/local/bin/scriptengine '$1
echo $PARAM
/usr/bin/xfce4-terminal -T “scriptengine” -x $PARAM

