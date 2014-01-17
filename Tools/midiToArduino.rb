#! /usr/bin/env ruby
require 'midilib/sequence'

usage = "Usage:\nruby midiToArduino.rb midi_file [--threshold threshold] [--arduinofile arduino_file]"

#Argument checks
if ARGV.length < 1
    puts "No input file\n"
    puts usage
    exit
else
    if not File.exists?(ARGV[0])
        puts "Can't find input file #{ARGV[0]}"
        puts usage
        exit
    end
end

threshold = ARGV.index '--threshold'
if threshold != nil
    threshold = ARGV[threshold + 1].to_i
else
    threshold = 400
end

#Initialization and information display
seq = MIDI::Sequence.new()
intput_file = File.open(ARGV[0], 'rb')

puts "Available tracks:"
seq.read(intput_file) do |track, num_tracks, i|
    if track
        puts "#{i - 1}: #{track.name} #{track.instrument ? track.instrument : ''}"
    end
end

pulse = seq.pulses_to_seconds(1)*1000
puts "\nBPM: #{seq.beats_per_minute} - Pulse: #{pulse} ms\n"

puts "Which track do you want to convert to Arduino tone?"
track_num = STDIN.gets.to_i


#Information gathering
track           = ""
arr_note_data   = Array.new
timestamp       = 0

seq.each_with_index do |track, i|
    note_on = false
    h = Hash.new

    if i == track_num
        track.each do |e|
            e.print_decimal_numbers = true
            e.print_note_names = true

            delta_time = (e.delta_time*pulse).to_i      #Time since last event in ms
            timestamp += delta_time

            if e.class.name == 'MIDI::NoteOn' || e.class.name == 'MIDI::NoteOff'
                if (not note_on) && (e.class.name == 'MIDI::NoteOn')
                    h['timestamp'] = timestamp
                    h['note']      = e.pch_oct
                    note_on        = true
                elsif note_on && (e.class.name == 'MIDI::NoteOff')
                    if e.pch_oct == h['note']
                        h['duration'] = timestamp - h['timestamp']
                        note_on       = false
                        arr_note_data << h.clone

                        puts h
                    end
                end
            end
        end
    end
end

if arr_note_data.length == 0
    puts "This track doesn't contant any note"
    exit
end

#Building the two arrays
arr_note     = Array.new
arr_duration = Array.new

arr_note_data.each_with_index do |note_data, index|
    if index == 0 && note_data['timestamp'] != 0
        arr_note     << 0
        arr_duration << note_data['timestamp']
    end

    if threshold < arr_note.length
        break
    end

    arr_note     << note_data['note']
    arr_duration << note_data['duration']

    if note_data != arr_note_data.last && note_data['timestamp'] + note_data['duration'] != arr_note_data[index + 1]['timestamp']
        arr_note << 0
        arr_duration << (arr_note_data[index + 1]['timestamp'] - note_data['timestamp'] - note_data['duration'])
    end
end

puts '-- Notes --'
puts arr_note

puts '-- Duration --'
puts arr_duration

do_output = ARGV.index '--arduinofile'
if do_output != nil
    if ARGV.length >= do_output + 2
        sketch = "/*************************************************\n * Public Constants\n *************************************************/\n#define NOTE_0   0\n#define NOTE_B0  31\n#define NOTE_C1  33\n#define NOTE_CS1 35\n#define NOTE_D1  37\n#define NOTE_DS1 39\n#define NOTE_E1  41\n#define NOTE_F1  44\n#define NOTE_FS1 46\n#define NOTE_G1  49\n#define NOTE_GS1 52\n#define NOTE_A1  55\n#define NOTE_AS1 58\n#define NOTE_B1  62\n#define NOTE_C2  65\n#define NOTE_CS2 69\n#define NOTE_D2  73\n#define NOTE_DS2 78\n#define NOTE_E2  82\n#define NOTE_F2  87\n#define NOTE_FS2 93\n#define NOTE_G2  98\n#define NOTE_GS2 104\n#define NOTE_A2  110\n#define NOTE_AS2 117\n#define NOTE_B2  123\n#define NOTE_C3  131\n#define NOTE_CS3 139\n#define NOTE_D3  147\n#define NOTE_DS3 156\n#define NOTE_E3  165\n#define NOTE_F3  175\n#define NOTE_FS3 185\n#define NOTE_G3  196\n#define NOTE_GS3 208\n#define NOTE_A3  220\n#define NOTE_AS3 233\n#define NOTE_B3  247\n#define NOTE_C4  262\n#define NOTE_CS4 277\n#define NOTE_D4  294\n#define NOTE_DS4 311\n#define NOTE_E4  330\n#define NOTE_F4  349\n#define NOTE_FS4 370\n#define NOTE_G4  392\n#define NOTE_GS4 415\n#define NOTE_A4  440\n#define NOTE_AS4 466\n#define NOTE_B4  494\n#define NOTE_C5  523\n#define NOTE_CS5 554\n#define NOTE_D5  587\n#define NOTE_DS5 622\n#define NOTE_E5  659\n#define NOTE_F5  698\n#define NOTE_FS5 740\n#define NOTE_G5  784\n#define NOTE_GS5 831\n#define NOTE_A5  880\n#define NOTE_AS5 932\n#define NOTE_B5  988\n#define NOTE_C6  1047\n#define NOTE_CS6 1109\n#define NOTE_D6  1175\n#define NOTE_DS6 1245\n#define NOTE_E6  1319\n#define NOTE_F6  1397\n#define NOTE_FS6 1480\n#define NOTE_G6  1568\n#define NOTE_GS6 1661\n#define NOTE_A6  1760\n#define NOTE_AS6 1865\n#define NOTE_B6  1976\n#define NOTE_C7  2093\n#define NOTE_CS7 2217\n#define NOTE_D7  2349\n#define NOTE_DS7 2489\n#define NOTE_E7  2637\n#define NOTE_F7  2794\n#define NOTE_FS7 2960\n#define NOTE_G7  3136\n#define NOTE_GS7 3322\n#define NOTE_A7  3520\n#define NOTE_AS7 3729\n#define NOTE_B7  3951\n#define NOTE_C8  4186\n#define NOTE_CS8 4435\n#define NOTE_D8  4699\n#define NOTE_DS8 4978\n\n"
        sketch << "int melody[] = {"
        arr_note.each do |note|
            sketch << "NOTE_#{note},".gsub('#', 'S')
        end

        sketch << "};\n\nint noteDurations[] = {"
        arr_duration.each do |duration|
            sketch << "#{duration},"
        end

        sketch << "};\n"
        sketch << "int number_of_note = #{arr_note.length};\n\n"

        sketch << "void setup(){}\n\nvoid loop(){\n\n"

        sketch << "  for (int thisNote = 0; thisNote < number_of_note; thisNote++) {\n    int noteDuration = noteDurations[thisNote];\n    tone(8, melody[thisNote],noteDuration);\n    int pauseBetweenNotes = noteDuration;\n    delay(pauseBetweenNotes);\n    noTone(8);\n  }\n"

        sketch << "}"
        out = File.open ARGV[do_output + 1], "w"
        out.write sketch
        out.close
    end
else
    sketch = ""
    sketch << "int melody[] = {"
    arr_note.each do |note|
        sketch << "NOTE_#{note},".gsub('#', 'S')
    end

    sketch << "};\n\nint noteDurations[] = {"
    arr_duration.each do |duration|
        sketch << "#{duration},"
    end

    sketch << "};\n"
    sketch << "int number_of_note = #{arr_note.length};\n\n"

    puts sketch;
end