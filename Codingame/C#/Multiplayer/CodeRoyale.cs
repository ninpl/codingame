// Rank: 3/.. - Wood 3 League 

using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

// To debug: Console.Error.WriteLine("Debug messages...");
class Program
{
    static void Main(string[] args)
    {
        World world = new World();
        world.Initialise(int.Parse(Console.ReadLine()));

        // game loop
        while (true)
        {
            world.UpdateState();
            Console.WriteLine(world.BuildActionString());
            Console.WriteLine(world.BuildTrainString());
        }
    }
}

public class World
{
    public World()
    { }

    public const int knightCost = 80;
    public const int archerCost = 100;
    public const int giantCost = 140;
    public List<Site> Sites { get; set; } = new List<Site>();
    public List<Unit> Units { get; set; } = new List<Unit>();
    public int Gold { get; set; }
    public int TouchedSite { get; set; }

    public void Initialise(int numSites)
    {
        for (int i = 0; i < numSites; i++)
        {
            string[] inputs = Console.ReadLine().Split(' ');
            var newSite = new Site
            (
                int.Parse(inputs[0]), //siteId
                new Point
                (
                    int.Parse(inputs[1]), //x
                    int.Parse(inputs[2]) //y
                ),
                int.Parse(inputs[3]) //radius
            );
            Sites.Add(newSite);
        }
    }

    public void UpdateState()
    {
        UpdateGlobals();
        UpdateSites();
        UpdateUnits(int.Parse(Console.ReadLine()));
    }

    public void UpdateGlobals()
    {
        string[] inputs = Console.ReadLine().Split(' ');
        Gold = int.Parse(inputs[0]);
        TouchedSite = int.Parse(inputs[1]); // -1 if none
    }

    public void UpdateSites()
    {
        for (int i = 0; i < Sites.Count(); i++)
        {
            string[] inputs = Console.ReadLine().Split(' ');
            Site updateSite = Sites.FirstOrDefault(site => site.SiteId == int.Parse(inputs[0])); //siteId
            //int ignore1 = int.Parse(inputs[1]); // used in future leagues
            //int ignore2 = int.Parse(inputs[2]); // used in future leagues
            StructureType type = (StructureType)int.Parse(inputs[3]);
            updateSite.Type = type;
            updateSite.Owner = (EntityOwner)int.Parse(inputs[4]);

            switch (type)
            {
                case StructureType.Barracks:
                    updateSite.BarracksTurnsUntilIdle = int.Parse(inputs[5]); //param1
                    updateSite.BarracksType = (UnitType)int.Parse(inputs[6]); //param2
                    break;
                case StructureType.Tower:
                    updateSite.TowerHealth = int.Parse(inputs[5]); //param1
                    updateSite.TowerAttackRadius = int.Parse(inputs[6]); //param2
                    break;
            }
        }
    }

    public void UpdateUnits(int numUnits)
    {
        Units.Clear();

        for (int i = 0; i < numUnits; i++)
        {
            string[] inputs = Console.ReadLine().Split(' ');
            var newUnit = new Unit
            (
                new Point
                (
                    int.Parse(inputs[0]), //x
                    int.Parse(inputs[1]) //y
                ),
                (EntityOwner)int.Parse(inputs[2]), //owner
                (UnitType)int.Parse(inputs[3]), //unitType
                int.Parse(inputs[4]) //health
            );
            Units.Add(newUnit);
        }
    }

    public string BuildActionString()
    {
        var action = "WAIT";
        var myQueen = Units.First(unit => unit.Type == UnitType.Queen && unit.Owner == EntityOwner.Friendly);

        try
        {
            var closestSite = Sites.Where(site => site.Owner == EntityOwner.None).OrderBy(site => Helpers.DistanceBetween(site.Location, myQueen.Location)).First();
            action = "BUILD " + closestSite.SiteId + " BARRACKS-KNIGHT";
        }
        catch
        { }

        return action;
    }

    public string BuildTrainString()
    {
        var train = "TRAIN";

        if (Gold >= 80)
        {
            try
            {
                Site trainSite = Sites.FirstOrDefault(site => site.Owner == EntityOwner.Friendly && site.Type == StructureType.Barracks && site.BarracksTurnsUntilIdle == 0);
                train += " " + trainSite.SiteId;
            }
            catch
            { }
        }

        return train;
    }
}

public class Site
{
    public Site(int siteId, Point location, int radius)
    {
        SiteId = siteId;
        Location = location;
        Radius = radius;
    }

    public int SiteId { get; }
    public Point Location { get; }
    public int Radius { get; }
    public StructureType Type { get; set; }
    public EntityOwner Owner { get; set; }
    public int BarracksTurnsUntilIdle { get; set; }
    public UnitType BarracksType { get; set; }
    public int TowerHealth { get; set; }
    public int TowerAttackRadius { get; set; }

}

public class Unit
{
    public Unit(Point location, EntityOwner owner, UnitType unitType, int health)
    {
        Location = location;
        Owner = owner;
        Type = unitType;
        Health = health;
    }
    public Point Location { get; }
    public EntityOwner Owner { get; }
    public UnitType Type { get; }
    public int Health { get; }
}

public static class Helpers
{
    public static double DistanceBetween(Point point1, Point point2)
    {
        var a = (double)(point2.x - point1.x);
        var b = (double)(point2.y - point1.y);

        return Math.Sqrt(a * a + b * b);
    }
}

public struct Point
{
    public int x, y;

    public Point(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
}

public enum StructureType { NoStructure = -1, Mine, Tower, Barracks }

public enum EntityOwner { None = -1, Friendly, Enemy }

public enum UnitType { Queen = -1, Knight, Archer, Giant }