#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QSoundEffect>

class AudioManager : public QObject {
    Q_OBJECT
public:
    enum SoundType { CardClick, CardPlay, Bomb, Win, Lose };
    static AudioManager* instance();
    void play(SoundType type);

private:
    explicit AudioManager(QObject *parent = nullptr);
    QMap<SoundType, QSoundEffect*> m_sounds;
};

#endif // AUDIOMANAGER_H
