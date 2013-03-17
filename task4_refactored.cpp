namespace MediaPlayer
{
  class Application
  {
  public:
    Application(): adapter(0)
    {
      // Чистим playlist
      for(std::list<MediaPlayer::Item*>::iterator it = playlist.begin();
        it != playlist.end(); ++it) {
        delete *it;
      }

      // Чистим список проигрывателей
      for(std::list<Base::SoundAdapter*>::iterator it = adapters.begin();
        it != adapters.end(); ++it) {
        delete *it;
      }
    }

    // Добавление элемента списка проигрывания в плеер
    void Open(const std::string& filename)
    {
      MediaPlayer::Item* item = new MediaPlayer::Item(filename);
      if(adapter)
      {
        item->setSoundAdapter(adapter);
      }
      playlist.push_back();
    }

    //
    void Play(const MediaPlayer::Item* item)
    {
      item->Play();
    }

    // Другие полезные методы
    ...

  private:
    Base::SoundAdapter* adapter;
    std::list<Base::SoundAdapter*> adapters;
    std::list<MediaPlayer::Item*> playlist;
  };
}
