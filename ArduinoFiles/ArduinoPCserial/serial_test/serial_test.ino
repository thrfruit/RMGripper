void setup()
{
    Serial.begin(115200);
}

void loop()
{
    if (Serial.available() > 0)
    {
        char incoming_byte = Serial.read();
        // take what we get and echo it right back
        Serial.write(incoming_byte);
    }
}
