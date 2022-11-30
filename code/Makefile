PIO=pio
ENVSTR=
ifdef PIOENV
	ENVSTR="-e"${PIOENV}
endif
BAUD_RATE=115200
DMX_BAUD_RATE=250000

compile: 
	${PIO} run ${ENVSTR}

upload-receiver: 
	PLATFORMIO_BUILD_FLAGS="-DBAUD_RATE=${BAUD_RATE}" \
			${PIO} run --target=upload -e receiver:wemosd1mini

upload-controller: 
	# hardcode the baud rate on the controller to the DMX baud rate
	#  its a little fast for most debugging / practical purposes so
	#  the receiver can run at a more manageable baud rate but the 
	#  DMX library is going to force it to 250mbps
	PLATFORMIO_BUILD_FLAGS="-DBAUD_RATE=${DMX_BAUD_RATE}" \
			${PIO} run --target=upload -e controller:wemosd1mini

receiver-logs: 
	${PIO} device monitor -b ${BAUD_RATE} ${ENVSTR} 

controller-logs: 
	${PIO} device monitor -b ${DMX_BAUD_RATE} ${ENVSTR} 

.PHONY: compile upload-receiver upload-controller receiver-logs controller-logs
