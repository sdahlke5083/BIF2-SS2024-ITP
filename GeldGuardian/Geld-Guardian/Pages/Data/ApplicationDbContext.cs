using Geld_Guardian.Pages.Data.Models;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;

namespace Geld_Guardian.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {

        public DbSet<Bill> Bills { get; set; }
        public DbSet<BillItem> BillItems { get; set; }

        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // Setting default value and computed column
            modelBuilder.Entity<Bill>()
                .Property(b => b.Status)
                .HasDefaultValue("Paid");

            // Configure BillItem with explicit foreign key to Bill
            modelBuilder.Entity<BillItem>()
                .HasOne(bi => bi.Bill) // Indicates that each BillItem has one Bill
                .WithMany(b => b.BillItems) // Indicates that a Bill can have many BillItems
                .HasForeignKey(bi => bi.BillId); // Explicitly sets BillId as the foreign key
        }

    }
}
