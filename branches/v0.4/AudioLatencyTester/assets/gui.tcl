package require Tcl 8.5
package require Tk 8.5

wm title . "Audio Latency Tester - Graphical Mode"
wm resizable . false false

variable sample_rate [get_sample_rate]
variable capture_size_scale_value [expr $sample_rate / 30]
variable capture_size_spinbox_value $capture_size_scale_value
variable expected_latency_spinbox_value [expr 1000 * $capture_size_scale_value / $sample_rate]

proc captureSizeSpinboxCallback {} {
	global sample_rate
	global capture_size_scale_value
	global expected_latency_spinbox_value
	
	variable capture_size [.captureSizeSpinbox get]
	
	set capture_size_scale_value $capture_size
	set expected_latency_spinbox_value [expr 1000 * $capture_size / $sample_rate]
	set_capture_size $capture_size
}

proc expectedLatencySpinboxCallback {} {
	global sample_rate
	global capture_size_scale_value
	global capture_size_spinbox_value
	
	variable capture_size [expr [.expectedLatencySpinbox get] * $sample_rate / 1000]
	
	set capture_size_scale_value $capture_size
	set capture_size_spinbox_value $capture_size
	set_capture_size $capture_size
}

proc captureSizeScaleCallback value {
	global sample_rate
	global capture_size_spinbox_value
	global expected_latency_spinbox_value
	
	variable capture_size [tcl::mathfunc::int $value]
	
	set capture_size_spinbox_value $capture_size
	set expected_latency_spinbox_value [expr 1000 * $capture_size / $sample_rate]
	set_capture_size $capture_size
}

pack [ttk::label ".captureSizeLabel" -text "Capture Size: "] -side left
pack [ttk::spinbox ".captureSizeSpinbox" -width 6 -state readonly -from 1 -to $sample_rate -textvariable capture_size_spinbox_value -command captureSizeSpinboxCallback] -side left
pack [ttk::label ".expectedLatencyLabel" -text "Expected Latency: "] -side left
pack [ttk::spinbox ".expectedLatencySpinbox" -width 4 -state readonly -from 0 -to 1000 -textvariable expected_latency_spinbox_value -command expectedLatencySpinboxCallback] -side left
pack [ttk::scale ".captureSizeScale" -length 480 -from 1 -to $sample_rate -variable capture_size_scale_value -command captureSizeScaleCallback] -side left