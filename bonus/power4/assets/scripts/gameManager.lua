function start(registry, gameContext)
    playMusicSound("gameManager", "audio/ambiance.ogg")
end

function update(registry, gameContext)

end

function exitGame(registry, gameContext)
    exitGame()
end

function play(registry, gameContext)
    print("Play")
    switchScene("game")
end