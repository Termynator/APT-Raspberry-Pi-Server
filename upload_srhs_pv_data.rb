#!/usr/bin/env ruby

require 'net/http'
require 'uri'
require 'json'
require 'httparty'
require 'socket'
include Socket::Constants


puts "*****************"

# Get the data from the inverter
# TODO: The inverter's values are hardcoded - should change this.
puts "Getting the data from inverter..."
s = UDPSocket.open
hostname = "10.101.5.8"
port = 14917
s.connect(hostname,port)
s.send([].pack("x48"), 0)
m = s.recvfrom(48)

# Unpack the data using a particular byte order - "Big Endian"
data = m[0].unpack("S*")
s.close

puts "OK - got the data from inverter..."

status = 0

if data[2] == 0x15
  status = 1
end

if data[2] == 0x18
  status = 2
end

dc_voltage = data[5] * 0.015441895
ac_voltage = data[8] * 0.018493652
ac_power = data[4] * 0.741699219
inv_temperature = data[7] * 0.01
total_kwh = data[16] + data[17]

puts "Data from inverter:"
puts dc_voltage
puts ac_voltage
puts ac_power
puts inv_temperature
puts total_kwh


# Calculate the incident angle using a solar position algorithm from NREL
# Usage of SPA is:
# spa <year> <month> <day> <hour> <minute> <second> <timezone> <delta_t> <longitude> <latitude> <elevation> <pressure> <temperature> <slope> <azm_rotation> <atmos_refract>
puts "Calculating the angle of incidence..."
date = Time.new()

#TODO: Must change for production
#TODO: Would be good to get the inverter values from the website first, currently they are hard coded.
spa_data = `/Users/stemple/RubymineProjects/aptweblab_old/lib/tasks/spa #{date.year} #{date.month} #{date.day} #{date.hour} #{date.min} 0 -8.0 64.797 -122.514 37.97 10 885 15 15.0 65 0.5667`

angle = spa_data.split[7].to_f

puts 'Got the angle from SPA: ' + angle.to_s

puts "Posting new inverter data to website..."

# TODO: Must change this for production!
# I use HTTParty here because it can handle nested parameters
res = HTTParty.post('http://www.aptweblab.org/pv_data', body: {pv_datum: {inverter_id: 1,
                                                                       temperature: inv_temperature,
                                                                       dc_voltage: dc_voltage,
                                                                       ac_voltage: ac_voltage,
                                                                       ac_power: ac_power,
                                                                       total_kwh: total_kwh,
                                                                       incident_angle: angle,
                                                                       status: status }}).body

puts res
puts "******************"
