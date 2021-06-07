using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum Notes
{
    C,
    Db,
    D,
    Eb,
    E,
    F,
    Gb,
    G,
    Ab,
    A,
    Bb,
    B
}

public class NoteFrequencyMap
{
    private static Dictionary<Notes, double> m_notes;

    static NoteFrequencyMap()
    {
        m_notes = new Dictionary<Notes, double>();
        m_notes.Add(Notes.C, 261.63);
        m_notes.Add(Notes.Db, 277.18);
        m_notes.Add(Notes.D, 293.66);
        m_notes.Add(Notes.Eb, 311.13);
        m_notes.Add(Notes.E, 329.63);
        m_notes.Add(Notes.F, 349.23);
        m_notes.Add(Notes.Gb, 369.99);
        m_notes.Add(Notes.G, 392.00);
        m_notes.Add(Notes.Ab, 415.30);
        m_notes.Add(Notes.A, 440.0);
        m_notes.Add(Notes.Bb, 466.16);
        m_notes.Add(Notes.B, 493.88);
    }

    public static double NoteToFrequency(Notes note)
    {
        if (m_notes.ContainsKey(note))
        {
            return m_notes[note];
        }

        Debug.LogWarning("Using a non mapped note!");
        return 0.0;
    }
}
