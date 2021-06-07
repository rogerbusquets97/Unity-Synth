using UnityEngine;

public enum OscillatorType
{
    Sine,
    Triangle,
    Square,
   // Saw
}

[System.Serializable]
public class Oscillator : MonoBehaviour
{
    [SerializeField]
    Notes note;

    [SerializeField]
    OscillatorType type;

    [SerializeField]
    [Range(0.0f, 1.0f)]
    float volume = 0.5f;

    double m_increment;
    double m_phase;
    double m_sampling_frequency = 44100;
    float  m_gain = 0.5f;

    Envelope envelope = new Envelope();

    private void Update()
    {
        envelope.Update();
    }
    public void OnKeyPressed()
    {
        envelope.KeyOn();
        //m_gain = volume;
    }

    public void OnKeyReleased()
    {
        envelope.KeyOff();
        //m_gain = 0.0f;
    }

    void OnAudioFilterRead(float[] data, int channels)
    {
        m_increment = NoteFrequencyMap.NoteToFrequency(note) * 2.0 * Mathf.PI / m_sampling_frequency;
        for (int i = 0; i < data.Length; i+= channels)
        {
            m_phase += m_increment;
            data[i] = GetSound(m_phase) * envelope.GetLevel();

            if (channels == 2)
            {
                data[i + 1] = data[i];
            }

            if (m_phase > (Mathf.PI * 2))
            {
                m_phase = 0;
            }
        }
    }

    float GetSound(double phase)
    {
        switch(type)
        { 
            case OscillatorType.Sine: return m_gain * Mathf.Sin((float)phase);
            case OscillatorType.Square: return Mathf.Sin((float)phase) > 0.0 ? m_gain : -m_gain;
            case OscillatorType.Triangle: return m_gain * Mathf.Asin(Mathf.Sin((float)phase));
            //case OscillatorType.Saw: return m_gain * ((2.0f / Mathf.PI) * ((float)phase * Mathf.PI * 1.0f / (float)phase) - (Mathf.PI * 2.0f));

            default:
                return 0.0f;
        }
    }
}
