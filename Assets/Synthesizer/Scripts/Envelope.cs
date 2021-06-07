using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Envelope
{
    public float attack = 0.001f;
    public float release = 0.003f;
    public float current = 0.0f;
    public bool sustain = false;
    public float amplifier = 1.0f;

    public float delta = 0.0f;

    public void KeyOn()
    {
        delta = 1.0f / (attack * 44100);
    }

    public void KeyOff()
    {
        delta = -1.0f / (release * 44100);
    }

    public void Update()
    {
        if (delta > 0.0f)
        {
            current += delta;
            if (current >= 1.0f)
            {
                current = 1.0f;
                if (!sustain) KeyOff();
            }
        }
        else
        {
            current = Mathf.Max(current + delta, 0.0f);
        }
    }

    public float GetLevel()
    {
        return current * amplifier;
    }
}
