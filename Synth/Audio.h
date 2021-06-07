#pragma once

#define PI 3.14159
#include <cmath>

namespace Audio
{
	struct sEnvelopeASDR
	{
		double dAttackTime;
		double dDecayTime;
		double dReleaseTime;

		double dSustainAmplitude;
		double dStartAmplitude;

		double dTriggerOnTime;
		double dTriggerOffTime;

		bool bNoteOn;

		sEnvelopeASDR()
		{
			dAttackTime = 0.01;
			dDecayTime = 0.01;
			dReleaseTime = 0.02;

			dSustainAmplitude = 0.8;
			dStartAmplitude = 1.0;

			dTriggerOnTime = 0.0;
			dTriggerOffTime = 0.0;

			bNoteOn = false;
		}

		double GetAmplitude(double i_time)
		{
			double dAmplitude = 0.0;

			double dLifeTime = i_time - dTriggerOnTime;

			if (bNoteOn)
			{
				// ADS

				// Attack
				if (dLifeTime <= dAttackTime)
				{
					dAmplitude = (dLifeTime / dAttackTime) * dStartAmplitude;
				}

				//Decay
				if (dLifeTime > dAttackTime && dLifeTime < (dAttackTime + dDecayTime))
				{
					dAmplitude = ((dLifeTime - dAttackTime) / dDecayTime) * (dSustainAmplitude - dStartAmplitude) + dStartAmplitude;
				}

				//Sustain
				if (dLifeTime > (dAttackTime + dDecayTime))
				{
					dAmplitude = dSustainAmplitude;
				}
			}
			else
			{
				//Release
				dAmplitude = (i_time - dTriggerOnTime) / dReleaseTime * (0.0 - dSustainAmplitude) + dSustainAmplitude;
			}

			if (dAmplitude <= 0.0001)
			{
				dAmplitude = 0.0;
			}

			return dAmplitude;
		}

		void NoteOn(double i_time)
		{
			dTriggerOnTime = i_time;
			bNoteOn = true;
		}

		void NoteOff(double i_time)
		{
			dTriggerOffTime = i_time;
			bNoteOn = false;
		}
	};

	enum class OscilatorType
	{
		Sine,
		Square,
		Triangle,
		Saw
	};

	double ToAngularVelocity(double i_hertz)
	{
		return i_hertz * 2 * PI;
	}

	double SineWave(double i_hertz, double i_amplitude, double i_time)
	{
		return i_amplitude * sin(ToAngularVelocity(i_hertz) * i_time);
	}

	double SquareWave(double i_hertz, double i_amplitude, double i_time)
	{
		double wave = sin(ToAngularVelocity(i_hertz) * i_time);
		return wave > 0.0 ? i_amplitude : -i_amplitude;
	}

	double TriangleWave(double i_hertz, double i_amplitude, double i_time)
	{
		return i_amplitude * asin(sin(ToAngularVelocity(i_hertz) * i_time)) * 2.0 / PI;
	}

	double SawWave(double i_hertz, double i_amplitude, double i_time)
	{
		return (2.0 / PI) * (i_hertz * PI * fmod(i_time, 1.0 / i_hertz) - (PI / 2.0));
	}

	double GetWaveSound(OscilatorType i_type, double i_hertz, double i_amplitude, double i_time)
	{
		switch (i_type)
		{
		case OscilatorType::Sine:
			return SineWave(i_hertz, i_amplitude, i_time);
		case OscilatorType::Square:
			return SquareWave(i_hertz, i_amplitude, i_time);
		case OscilatorType::Saw:
			return SawWave(i_hertz, i_amplitude, i_time);
		case OscilatorType::Triangle:
			return TriangleWave(i_hertz, i_amplitude, i_time);
		default:
			return 0.0;
		}

		return 0.0;
	}




}